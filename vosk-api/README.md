This is the attempt to create the lib   https://github.com/k3b/vosk-api
in gradle only without any bash script.

---

what i have done so far:

* analysed build-vosk.sh
  * vosk depends on 'https://github.com/xianyi/OpenBLAS.git' which already has a cmake OpenBLAS/CMakeLists.txt

Created a new android project with a ndk subproject "vosk-api"

* has a gradle step to download 'https://github.com/xianyi/OpenBLAS.git' to 'vosk-api/src/main/cpp/clonedRepositories/OpenBLAS' 
  * (see [settings.gradle in project root](https://github.com/k3b/vosk-api-jitpack.io/blob/master/settings.gradle))
* vosk-api/src/main/cpp/CMakeLists.txt includes  vosk-api/src/main/cpp/clonedRepositories/OpenBLAS/CMakeLists.txt

what goes wrong: config.h is not generated in vosk-api/src/main/cpp/clonedRepositories/OpenBLAS/Makefile.system