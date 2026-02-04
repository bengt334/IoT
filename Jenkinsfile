pipeline {
    agent any
    environment {
        ZEPHYR_IMAGE = 'my-zephyr-codechecker:latest'
        BOARD       = 'esp32s3_devkitc/esp32s3/procpu'
        APP_PATH    = 'IoT'          // app lives inside cloned repo
    }
    stages {
        stage('Checkout') {
            steps {
                git url: 'https://github.com/bengt334/IoT.git',
                    branch: 'master'
            }
        }

        stage('Zephyr build + CodeChecker in Docker') {
            steps {
                script {
                    def ws = pwd()
                    sh """
                        docker run --rm \\
                            -v "${ws}":/workdir/${APP_PATH} \\
                            -w /workdir \\
                            ${ZEPHYR_IMAGE} \\
                            /bin/bash -lc '
                                set -e
                                echo "CWD:"; pwd
                                ls
                                source /home/user/cc-venv/bin/activate
                                CodeChecker version
                                # Ensure CodeChecker is installed in the image (pip or package)
                                if ! command -v CodeChecker >/dev/null 2>&1; then
                                    pip install codechecker
                                fi

                                # Init Zephyr workspace if needed
                                if [ ! -d ".west" ]; then
                                    west init -l ${APP_PATH}
                                    west update
                                fi

                                ls ${APP_PATH}

                                # 1) Log the build with CodeChecker
                                CodeChecker log -o compile_commands.json -b 'west build -b ${BOARD} ${APP_PATH} --pristine'

                                # 2) Analyze
                                CodeChecker analyze compile_commands.json -o cc_reports

                                # Optional: create HTML from reports for easier viewing
                                CodeChecker parse cc_reports -e html -o cc_html

                                ls -R cc_reports cc_html
                            '
                    """

                    // Collect reports as Jenkins artifacts
                    sh 'ls -R'
                }
            }
        }

        stage('Archive CodeChecker reports') {
            steps {
                archiveArtifacts artifacts: 'cc_reports/**, cc_html/**', allowEmptyArchive: true
            }
        }
    }
}


