#include <osgEarth/Version>
#define OSGEARTH_GIT_SHA1_STRING "GITDIR-NOTFOUND"
extern "C" {
    const char* osgEarthGitSHA1() {
        return OSGEARTH_GIT_SHA1_STRING;
    }
}
