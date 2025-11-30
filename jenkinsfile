pipeline {
    agent {
        docker {
            image 'zephyrprojectrtos/zephyr-build:v0.28.4' //or your own derived image
            args 'u jenkins:jenkins // if needed fir uid/gid
        }
    }
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        
        stage('Build') {
            steps {
                sh ''' 
                west init -l app || true
                west update
                west build -b & native_sim app
                '''
            }
        }
    }    
}
