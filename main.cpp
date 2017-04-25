#include "wrapsyncfs.h"

#include <fuse.h>
#include <iostream>
#include <fstream>
using namespace std;

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

	std::cout << "mounting file system...\n";
	
	if(argc < 4)
    {
        cout << "Command: syncmount path_to_folder_1 path_to_folder_2 path_to_mnt_point" << "\n"; 
        return -1;
    }

	//set_rootdir(realpath(argv[1], NULL),realpath(argv[2], NULL));

    char* argvf[argc-2];
    int argcf = argc-2;
    int a = 1;
    argvf[0] = argv[0];
	for(i=3; i < argc; i++) {
		argvf[a] = argv[i];
        cout << argvf[a] << " " << argcf << "\n";
        a++;
	}

	fuse_stat = fuse_main(argcf, argvf, &syncfs_oper, NULL);

	std::cout << "fuse_main returned "<<fuse_stat<<"\n";

	return fuse_stat;
}
