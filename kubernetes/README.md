# Kubernetes

### App

```console
    $docker build . -t dockerHubRepo/simple-app
    $docker login
    $docker push dockerHubRepo/simple-app
```

### Minikube

#### Imperative
```console
    $minikube start --driver=docker
    $minikube status
    $minikube dashboard

    # Create deployment object
    # This is a Kubernetes object that can create, manage and autoscale a set of identical pods
    $kubectl create deployment simple-app --image=pathToImageOnDockerhub
    $kubectl get deployments
    $kubectl get pods

    # Create service (types are ClusterIp, NodePort, LoadBancer )
    # Service object exposes pods to other pods in a clust or outside world
    $kubectl expose deployment simple-app --type=LoadBalancer --port=8080
    $kubectl get services
    $minikube service simple-app

    # Scaling
    $kubectl scale deployment/simple-app --replicas=3
    
    # Update image of existing deployment
    $kubectl set image deployment/simple-app containerName=pathToImageOnDockerhub:tag

    # Check status of deployment
    $kubectl rollout status deployment/simple-app
    $kubectl rollout history deployment/simple-app
    $kubectl rollout history deployment/simple-app --revision=2
    $kubectl rollout undo deployment/simple-app
    $kubectl rollout undo deployment/simple-app --to-revision=1

    # Cleanup
    $kubectl delete service simple-app
    $kubectl delete deployment simple-app

```

#### Declarative
```console
    # Create service and deployment
    $kubectl apply -f=deployment.yml
    $kubectl apply -f=service.yml
    $minikube service simple-service

    # Clean up resources
    $kubectl delete -f=deployment.yml -f=service.yml
    
    # Both deplyoment.yml and service.yml can be merged into same file but had to be be separeted with line containing "---"
```
