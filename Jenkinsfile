pipeline {
    agent {
        docker {
            image 'zephyrprojectrtos/ci:latest'
            args 'u root:root'
        }
    }

    environment {
        BOARD = 'esp32s3_devkitc/esp32s3/procpu'
        APP_PATH = '.'
    }
    stages {
        stage('Checkout') {
            steps { 
                git branch: 'main',
                    url:'https://github.com/bengt334/IoT'
            }
        }
        stage('West init/update') {
            steps {
                sh '''
                    if [ ! -d .west ]; then 
                        west init -l ${APP_PATH}
                        west update
                    fi
                '''
            }
        }
        stage('Build') {
            steps {
                sh '''
                    west build -b ${BOARD} ${APP_PATH} -fingerprinthuhuhuh-pristine
                '''
            }
        }
        stage('Artifacts') {
            steps {
                archiveArtifacts artifacts: 'build/zephyr/zephyr.*',
                    fingerprint:true
            }
        }
    }
}
