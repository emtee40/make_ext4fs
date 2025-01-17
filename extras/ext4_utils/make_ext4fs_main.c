/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <unistd.h>

#if defined(__linux__)
#include <linux/fs.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include <sys/disk.h>
#endif

#ifdef ANDROID
#include <private/android_filesystem_config.h>
#endif
#ifndef O_BINARY
#define O_BINARY 0
#endif
#include <selinux/selinux.h>
#include <selinux/label.h>
#include <selinux/android.h>

#include "ext4_utils.h"
#include "canned_fs_config.h"

#ifndef O_BINARY /* O_BINARY is windows-specific flag */
#define O_BINARY 0
#endif

extern struct fs_info info;


static void usage(char *path)
{
	fprintf(stderr, "%s [ -l <len> ] [ -j <journal size> ] [ -b <block_size> ]\n", basename(path));
	fprintf(stderr, "    [ -g <blocks per group> ] [ -i <inodes> ] [ -I <inode size> ]\n");
	fprintf(stderr, "    [ -L <label> ] [ -f ] [ -a <android mountpoint> ]\n");
	fprintf(stderr, "    [ -S file_contexts ] [ -C fs_config ] [ -T timestamp ]\n");
	fprintf(stderr, "    [ -z | -s ] [ -w ] [ -c ] [ -J ] [ -v ] [ -B <block_list_file> ]\n");
	fprintf(stderr, "    <filename> [<directory>]\n");
}

int main(int argc, char **argv)
{
	int opt;
	const char *filename = NULL;
	const char *directory = NULL;
	char *mountpoint = NULL;
	fs_config_func_t fs_config_func = NULL;
	const char *fs_config_file = NULL;
	int gzip = 0;
	int sparse = 0;
	int crc = 0;
	int wipe = 0;
	int fd;
	int exitcode;
	int verbose = 0;
	time_t fixed_time = -1;
	struct selabel_handle *sehnd = NULL;
	FILE* block_list_file = NULL;
	struct selinux_opt seopts[] = { { SELABEL_OPT_PATH, "" } };

	while ((opt = getopt(argc, argv, "l:j:b:g:i:I:L:a:S:T:C:B:fwzJsctv")) != -1) {
		switch (opt) {
		case 'l':
			info.len = parse_num(optarg);
			break;
		case 'j':
			info.journal_blocks = parse_num(optarg);
			break;
		case 'b':
			info.block_size = parse_num(optarg);
			break;
		case 'g':
			info.blocks_per_group = parse_num(optarg);
			break;
		case 'i':
			info.inodes = parse_num(optarg);
			break;
		case 'I':
			info.inode_size = parse_num(optarg);
			break;
		case 'L':
			info.label = optarg;
			break;
		case 'f':
			force = 1;
			break;
		case 'a':
#ifdef ANDROID
			mountpoint = optarg;
#else
			fprintf(stderr, "can't set android permissions - built without android support\n");
			usage(argv[0]);
			exit(EXIT_FAILURE);
#endif
			break;
		case 'w':
			wipe = 1;
			break;
		case 'z':
			gzip = 1;
			break;
		case 'J':
			info.no_journal = 1;
			break;
		case 'c':
			crc = 1;
			break;
		case 's':
			sparse = 1;
			break;
		case 't':
			fprintf(stderr, "Warning: -t (initialize inode tables) is deprecated\n");
			break;
		case 'S':
			seopts[0].value = optarg;
			sehnd = selabel_open(SELABEL_CTX_FILE, seopts, 1);
			if (!sehnd) {
				perror(optarg);
				exit(EXIT_FAILURE);
			}
			break;
		case 'v':
			verbose = 1;
			break;
		case 'T':
			fixed_time = strtoll(optarg, NULL, 0);
			break;
		case 'C':
			fs_config_file = optarg;
			break;
		case 'B':
			block_list_file = fopen(optarg, "w");
			if (block_list_file == NULL) {
				fprintf(stderr, "failed to open block_list_file: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			break;
		default: /* '?' */
			usage(argv[0]);
			exit(EXIT_FAILURE);
		}
	}

#if !defined(HOST)
	// Use only if -S option not requested
	if (!sehnd && mountpoint) {
		sehnd = selinux_android_file_context_handle();

		if (!sehnd) {
			perror(optarg);
			exit(EXIT_FAILURE);
		}
	}
#endif

	if (fs_config_file) {
		if (load_canned_fs_config(fs_config_file) < 0) {
			fprintf(stderr, "failed to load %s\n", fs_config_file);
			exit(EXIT_FAILURE);
		}
		fs_config_func = canned_fs_config;
	} else if (mountpoint) {
		fs_config_func = fs_config;
	}

	if (wipe && sparse) {
		fprintf(stderr, "Cannot specifiy both wipe and sparse\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (wipe && gzip) {
		fprintf(stderr, "Cannot specifiy both wipe and gzip\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (optind >= argc) {
		fprintf(stderr, "Expected filename after options\n");
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	filename = argv[optind++];

	if (optind < argc)
		directory = argv[optind++];

	if (optind < argc) {
		fprintf(stderr, "Unexpected argument: %s\n", argv[optind]);
		usage(argv[0]);
		exit(EXIT_FAILURE);
	}

	if (strcmp(filename, "-")) {
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0644);
		if (fd < 0) {
			perror("open");
			return EXIT_FAILURE;
		}
	} else {
		fd = STDOUT_FILENO;
	}

	exitcode = make_ext4fs_internal(fd, directory, mountpoint, fs_config_func, gzip,
		sparse, crc, wipe, sehnd, verbose, fixed_time, block_list_file);
	close(fd);
	if (block_list_file)
		fclose(block_list_file);
	if (exitcode && strcmp(filename, "-")) {
		fprintf(stderr, "Failed to create image %s, removing it\n", filename);
		unlink(filename);
	}
	return exitcode;
}
