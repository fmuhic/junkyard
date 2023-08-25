package com.example.akkaactormodel

import akka.actor.typed.ActorSystem
import com.example.akkaactormodel.actor.prime.InstructionManagerCommand
import com.example.akkaactormodel.actor.prime.ManagerBehavior
import com.example.akkaactormodel.actor.prime.ManagerCommand
import com.example.akkaactormodel.actor.SimpleBehavior
import com.example.akkaactormodel.classic.MultiThreadedPrimeGenerator
import com.example.akkaactormodel.classic.SingleThreadedPrimeGenerator
import org.springframework.boot.context.event.ApplicationReadyEvent
import org.springframework.context.event.EventListener
import org.springframework.stereotype.Service

@Service
class Runner(
    private val singleThreadedPrimeGenerator: SingleThreadedPrimeGenerator,
    private val multiThreadedPrimeGenerator: MultiThreadedPrimeGenerator
) {
    @EventListener(ApplicationReadyEvent::class)
    fun start() {
//        startClassic()
//        startSimpleActor()
        startPrimeNumberActor()
    }

    private fun startPrimeNumberActor() {
        val primeManager: ActorSystem<ManagerCommand> = ActorSystem.create(ManagerBehavior.create(), "PrimeManager")
        primeManager.tell(InstructionManagerCommand("start"))
    }

    private fun startSimpleActor() {
        val simpleActorSystem: ActorSystem<String> = ActorSystem.create(SimpleBehavior.create(), "SimpleActorSystem")
        simpleActorSystem.tell("say hello")
        simpleActorSystem.tell("who are you")
        simpleActorSystem.tell("create child")
    }

    private fun startClassic() {
        val start = System.currentTimeMillis()
        multiThreadedPrimeGenerator.generatePrimeNumbers(20)
        val duration = System.currentTimeMillis() - start
        println("Calculation took $duration ms")
    }
}