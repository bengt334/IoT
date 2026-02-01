pipeline {
    agent any 
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
                            -v "${ws}":/workdir/IoT \
                            -w /workdir \
                            ${ZEPHYR_IMAGE} \
                            /bin/bash -lc '
                                set -e
                                echo "CWD:"; pwd
                                ls
                                #initiera zephyr workspace om det inte redan finns
                                if [ ! -d "IoT/.west" ]; then 
                                    west init -l IoT
                                    west update
                                fi
                                #Anpassa board och app path
                                ls IoT
                                west build -b ${BOARD} IoT --pristine
                                echo "=== Build output ==="
                                ls -l
                                echo "=== WHO OWNS THE WORKSPACE? ==="
                                ls -ld .
                                ls -ld IoT
                                ls -ld build/zephyr
                                ls -l build/zephyr | head
                                id
                                cp build/zephyr/zephyr.elf IoT/zephyr.elf
                            '
                    """
                    sh "ls -R ."
                    archiveArtifacts artifacts: 'IoT/*.elf, IoT/*.bin, IoT/*.hex', fingerprint:true
                }
            }
        }
    }
}
