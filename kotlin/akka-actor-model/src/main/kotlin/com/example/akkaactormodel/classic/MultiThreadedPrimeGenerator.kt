package com.example.akkaactormodel.classic

import org.springframework.stereotype.Service
import java.math.BigInteger
import java.util.*
import java.util.concurrent.Callable
import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors

@Service
class MultiThreadedPrimeGenerator {
    val workerPool: ExecutorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors())
    fun generatePrimeNumbers(count: Int): Set<BigInteger> = ConcurrentHashMap.newKeySet<BigInteger>().also { primes ->
        val tasks = (0 until count).map {
            Callable {
                val bigNumber = BigInteger(1500, Random())
                primes.add(bigNumber.nextProbablePrime())
                print(".")
            }
        }
        workerPool.invokeAll(tasks)
        workerPool.shutdown()
        println()
    }
}