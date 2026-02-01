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
                      docker run --rm \
                          -u ${uid}:${gid} \
                          -v "${ws}":/workdir \
                          -w /workdir \
                          ${ZEPHYR_IMAGE} \
                          /bin/bash -lc '
                              set -e
                              echo "=== DEBUG ==="
                              echo "whoami:"; whoami
                              echo "pwd before anything:"; pwd
                              echo "ls:"; ls
                              echo "which west:"; which west || echo "no west in PATH"
                              echo "env WEST_*:"; env | grep ^WEST_ || echo "no WEST_* vars"

                              echo "west.yml here?"; ls -l west.yml || echo "NO west.yml"

                              echo "Running: west init --local ."
                              WEST_WORKSPACE=/workdir west init --local .

                              echo "Running: west update"
                              WEST_WORKSPACE=/workdir west update

                              echo "Running: west build -b ${BOARD} . --pristine"
                              WEST_WORKSPACE=/workdir west build -b ${BOARD} . --pristine

                              echo "Copying elf"
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
