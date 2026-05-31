#include <CoreFoundation/CoreFoundation.h>

static int resolve(char *path, char *resolvedPath) {
    CFURLRef URL, resolvedURL;
    CFDataRef bookmark;

    if ((URL = CFURLCreateFromFileSystemRepresentation(NULL, (const UInt8 *)path, strlen(path), false))
        && (bookmark = CFURLCreateBookmarkDataFromFile(NULL, URL, NULL))
        && (resolvedURL = CFURLCreateByResolvingBookmarkData(NULL, bookmark, kCFURLBookmarkResolutionWithoutUIMask, NULL, NULL, NULL, NULL))) {
            CFURLGetFileSystemRepresentation(resolvedURL, false, (UInt8 *)resolvedPath, PATH_MAX);
            return 0;
    } else {
        return 1;
    }

}

int main(int argc,  char *argv[]) {
    char *programName, *path;
    char resolvedPath[PATH_MAX];
    int status, ch, cflag;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s file\n", programName);
        return 1;
    }
    programName = argv[0];
    path = argv[1];
    status = resolve(path, resolvedPath);
    if (status == 0)
        printf("%s\n", resolvedPath);
    else
        fprintf(stderr, "%s: %s: Not a Finder alias or failed to resolve\n", programName, path);
    return status;
}
