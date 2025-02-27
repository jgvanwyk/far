#include <CoreFoundation/CoreFoundation.h>

#define PROGRAM_NAME "far"
#define USAGE "usage: " PROGRAM_NAME " file...\n"

int main(int argc, char *argv[])
{
    CFURLRef source, target;
    CFDataRef bookmark;
    CFErrorRef error;
    char path[PATH_MAX];

    if (argc <= 1) {
        fprintf(stderr, USAGE);
        return 1;
    }

    for (--argc, ++argv; argc > 0; --argc, ++argv) {
        source = CFURLCreateFromFileSystemRepresentation(NULL, (UInt8 *)*argv, strlen(*argv), false);
        bookmark = CFURLCreateBookmarkDataFromFile(NULL, source, &error);
        if (!bookmark) {
            fprintf(stderr, PROGRAM_NAME ": %s: is not a Finder alias\n", *argv);
            CFRelease(error);
            CFRelease(source);
            return 2;
        }
        target = CFURLCreateByResolvingBookmarkData(NULL, bookmark, 0, NULL, NULL, NULL, &error);
        if (!target) {
            fprintf(stderr, PROGRAM_NAME ": %s: could not resolve alias\n", *argv);
            CFRelease(error);
            CFRelease(source);
            CFRelease(bookmark);
            return 3;
        }
        CFURLGetFileSystemRepresentation(target, false, (UInt8 *)path, PATH_MAX);
        printf("%s\n", path);
        CFRelease(source);
        CFRelease(bookmark);
        CFRelease(target);
        error = NULL;
    }

    return 0;
}
