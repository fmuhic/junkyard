package com.example.akkaactormodel.actor.prime

import akka.actor.typed.Behavior
import akka.actor.typed.javadsl.AbstractBehavior
import akka.actor.typed.javadsl.ActorContext
import akka.actor.typed.javadsl.Behaviors
import akka.actor.typed.javadsl.Receive
import java.io.Serializable
import java.math.BigInteger
import java.util.*

class ManagerBehavior private constructor(
    private val context: ActorContext<ManagerCommand>
): AbstractBehavior<ManagerCommand>(context) {

    companion object {
        fun create(): Behavior<ManagerCommand> = Behaviors.setup(::ManagerBehavior)
    }

    private val workerCount = 20
    private val primes: SortedSet<BigInteger> = TreeSet()

    override fun createReceive(): Receive<ManagerCommand> =
        newReceiveBuilder()
            .onMessage(InstructionManagerCommand::class.java) { command ->
                when (command.msg) {
                    "start" -> {
                        repeat(workerCount) {
                            val worker = context.spawn(WorkerBehavior.create(), "Worker$it")
                            worker.tell(WorkerCommand("start", context.self))
                        }
                    }
                    else -> {}
                }
                return@onMessage this
            }
            .onMessage(ResultManagerCommand::class.java) { command ->
                primes.add(command.result)
                if (primes.size == workerCount) {
                    println("Operation Done $primes")
                } else {
                    println(".")
                }
                return@onMessage this
            }
            .build()
}

interface ManagerCommand: Serializable

class InstructionManagerCommand(
    private val actorMsg: String
): ManagerCommand {
    val msg get() = actorMsg
}

class ResultManagerCommand(
    private val actorResult: BigInteger
): ManagerCommand {
    val result get() = actorResult
}
