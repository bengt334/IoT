pipeline {
    agent {
        node {
            label ''
            customWorkspace '/var/lib/jenkins/workspace/BengtnZephyrIoT_master'
        }
    }
    environment {
        ZEPHYR_IMAGE = 'zephyrprojectrtos/zephyr-build:latest'
        BOARD = 'esp32s3_devkitc/esp32s3/procpu'
        APP_PATH = '.'
    }
    stages {
        stage('Checkout') {
            steps { 
                git url: 'https://github.com/bengt334/IoT.git', 
                branch: 'master'
            }
        }
        stage('Zephyr build in Docker') {
            steps {
                script {
                    def ws = pwd()
                    def uid = sh(returnStdout: true, script: "id -u").trim()
                    def gid = sh(returnStdout: true, script: "id -g").trim()
                    sh """
                        docker pull ${ZEPHYR_IMAGE}
                        docker run --rm \\
                            -u ${uid}:${gid} \\
                            -v "${ws}":/workdir \\
                            -w /workdir \\
                            ${ZEPHYR_IMAGE} \\
                            /bin/bash -lc '
                      set -e
                      echo "CWD:"; pwd
                      ls
                      echo "west.yml here?"; ls -l west.yml || echo "NO west.yml"

                      # Init Zephyr workspace if needed
                      if [ ! -d ".west" ]; then
                          west init --local .
                          west update
                      fi

                      # Build this repo as the app
                      west build -b ${BOARD} . --pristine

                      echo "=== Build output ==="
                      ls -l
                      echo "=== WHO OWNS THE WORKSPACE? ==="
                      ls -ld .
                      ls -ld build/zephyr
                      ls -l build/zephyr | head
                      id

                      cp build/zephyr/zephyr.elf zephyr.elf
                      '
                """
                sh "ls -R ."
                archiveArtifacts artifacts: '*.elf, *.bin, *.hex', fingerprint:true
                }
            }
        }
    }
}
