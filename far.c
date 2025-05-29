#include <CoreFoundation/CoreFoundation.h>

#define PROGNAME "far"
#define USAGE "usage: " PROGNAME " file...\n"

int main(int argc,  char *argv[]) {
    int ret;
    CFURLRef srcurl, trgurl;
    CFDataRef bookmarkdata;
    char trgpath[PATH_MAX];

    if (argc <= 1) {
        fprintf(stderr, USAGE);
        return 1;
    }
    ret = 0;
    for (--argc, ++argv; argc > 0; --argc, ++argv) {
        srcurl = CFURLCreateFromFileSystemRepresentation(NULL, (UInt8 *)*argv, strlen(*argv), false);
        bookmarkdata = CFURLCreateBookmarkDataFromFile(NULL, srcurl, NULL);
        if (bookmarkdata) {
            trgurl = CFURLCreateByResolvingBookmarkData(NULL, bookmarkdata, 0, NULL, NULL, NULL, NULL);
            if (trgurl) {
                CFURLGetFileSystemRepresentation(trgurl, false, (UInt8 *)trgpath, PATH_MAX);
                printf("%s\n", trgpath);
                CFRelease(trgurl);
            } else {
                ret = 1;
                fprintf(stderr, PROGNAME ": %s: Could not resolve Finder alias\n", *argv);
            }
            CFRelease(bookmarkdata);
        } else {
            printf("%s\n", *argv);
        }
        CFRelease(srcurl);
    }
    return ret;
}
