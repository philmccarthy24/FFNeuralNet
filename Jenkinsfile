pipeline {
  agent any
  stages {
    stage('Build') {
      steps {
        cmakeBuild(installation: 'InSearchPath', generator: 'Visual Studio 15 2017', cmakeArgs: '-DCMAKE_TOOLCHAIN_FILE="${VCPKG_ROOT}\\scripts\\buildsystems\\vcpkg.cmake"', buildDir: 'build')
        cmake(installation: 'InSearchPath', arguments: '--build . --config Release', workingDir: 'build')
      }
    }
  }
}