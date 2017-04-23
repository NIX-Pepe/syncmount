#include "wrapsyncfs.h"

#include <fuse.h>
#include <stdio.h>

struct fuse_operations syncfs_oper;

int main(int argc, char **argv) {
    int i, fuse_stat;

	syncfs_oper.getattr = wrap_getattr;
	syncfs_oper.readlink = wrap_readlink;
	syncfs_oper.getdir = NULL;
	syncfs_oper.mknod = wrap_mknod;
	syncfs_oper.mkdir = wrap_mkdir;
	syncfs_oper.unlink = wrap_unlink;
	syncfs_oper.rmdir = wrap_rmdir;
	syncfs_oper.symlink = wrap_symlink;
	syncfs_oper.rename = wrap_rename;
	syncfs_oper.link = wrap_link;
	syncfs_oper.chmod = wrap_chmod;
	syncfs_oper.chown = wrap_chown;
	syncfs_oper.truncate = wrap_truncate;
	syncfs_oper.utime = wrap_utime;
	syncfs_oper.open = wrap_open;
	syncfs_oper.read = wrap_read;
	syncfs_oper.write = wrap_write;
	syncfs_oper.statfs = wrap_statfs;
	syncfs_oper.flush = wrap_flush;
	syncfs_oper.release = wrap_release;
	syncfs_oper.fsync = wrap_fsync;
	syncfs_oper.setxattr = wrap_setxattr;
	syncfs_oper.getxattr = wrap_getxattr;
	syncfs_oper.listxattr = wrap_listxattr;
	syncfs_oper.removexattr = wrap_removexattr;
	syncfs_oper.opendir = wrap_opendir;
	syncfs_oper.readdir = wrap_readdir;
	syncfs_oper.releasedir = wrap_releasedir;
	syncfs_oper.fsyncdir = wrap_fsyncdir;
	syncfs_oper.init = wrap_init;

	printf("mounting file system...\n");
	
	for(i = 1; i < argc && (argv[i][0] == '-'); i++) {
		if(i == argc) {
			return (-1);
		}
	}

	//realpath(...) returns the canonicalized absolute pathname
	set_rootdir(realpath(argv[i], NULL));

	for(; i < argc; i++) {
		argv[i] = argv[i+1];
	}
	argc--;

	fuse_stat = fuse_main(argc, argv, &syncfs_oper, NULL);

	printf("fuse_main returned %d\n", fuse_stat);

	return fuse_stat;
}
