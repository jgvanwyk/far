#include <Foundation/Foundation.h>
#include <stdio.h>
#include <sys/stat.h>

#define PROGNAME "far"
#define USAGE "Usage: " PROGNAME " [-q] file...\n"

int main(int argc,  char *argv[]) {
    int c, qflag, ret;
    NSURL *URL;
    NSData *data;
    struct stat st;

    ret = 0;
    opterr = 0;
    qflag = 0;
    while ((c = getopt(argc, argv, "q")) != -1) {
        switch (c) {
            case 'q':
                qflag = 1;
                break;
            case '?':
                fprintf(stderr, PROGNAME ": Invalid option: -%c\n", optopt);
                // Fallthrough
            default:
                fprintf(stderr, USAGE);
                return 2;
        }
    }
    argc -= optind;
    argv += optind;
    if (argc == 0) {
        fprintf(stderr, USAGE);
        return 2;
    }
    @autoreleasepool {
        for (; argc > 0; argc--, argv++) {        
            if (stat(*argv, &st) == 0) {
                if (!S_ISDIR(st.st_mode)) {
                    URL = [NSURL fileURLWithFileSystemRepresentation:*argv isDirectory:NO relativeToURL:nil];
                    data = [NSURL bookmarkDataWithContentsOfURL:URL error:NULL];
                    if (data) {
                        URL = [NSURL URLByResolvingBookmarkData:data
                                                        options:NSURLBookmarkResolutionWithoutUI
                                                  relativeToURL:nil 
                                            bookmarkDataIsStale:NULL
                                                          error:NULL];
                        if (URL) {
                            if (!qflag)
                                printf("%s\n", [URL fileSystemRepresentation]);
                            continue;
                        }
                    }
                }
                ret = 1;
                if (qflag)
                    break;
                printf("%s\n", *argv);
            } else {
                fprintf(stderr, PROGNAME ": %s: %s\n", strerror(errno), *argv);
                ret = 2;
            }
        }
        return ret;
    }
}
