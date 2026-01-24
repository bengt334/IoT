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
                    sh """
                        docker pull  ${ZEPHYR_IMAGE}
                        docker run --rm \
                            -v "${ws}":/workdir/repo \
                            -w /workdir \
                            ${ZEPHYR_IMAGE} \
                            /bin/bash -lc '
                                set -e
                                echo "CWD:"; pwd
                                ls
                                #initiera zephyr workspace om det inte redan finns
                                if [ ! -d ".west" ]; then 
                                    west init -l repo
                                    west update
                                fi
                                #Anpassa board och app path
                                ls .
                                west build -b ${BOARD} IoT --pristine
                            '
                    """
                }
            }
        }
        stage('Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/zephyr/*.elf, build/zephyr/*.bin, build/zephyr/*.hex,',
                    fingerprint:true
            }
        }
    }
}
