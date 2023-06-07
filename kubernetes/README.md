# Kubernetes

### Minikube
```sh
    $minikube start --driver=docker
    $minikube status
    $minikube dashboard

    # Create deployment
    $kubectl create deployment simple-app --image=pathToImageOnDockerhub
    $kubectl get deployments
    $kubectl get pods

    # Create service (types are ClusterIp, NodePort, LoadBancer )
    $kubectl expose deployment simple-app --type=LoadBalancer --port=8080
    $kubectl get services
    $minikube service simple-app
```
