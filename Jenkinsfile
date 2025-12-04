pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build with Docker') {
            steps {
                sh '''
                    docker run --rm \
                        -v $PWD:/workspace \
                        -w /workspace \
                        zephyrprojectrtos/zephyr-build:latest \
                        sh -c "
                            west init -l . &&
                            west update &&
                            west build -b nrf52840dk_nrf52840 app/
                        "
                '''
            }
        }
    }
}
