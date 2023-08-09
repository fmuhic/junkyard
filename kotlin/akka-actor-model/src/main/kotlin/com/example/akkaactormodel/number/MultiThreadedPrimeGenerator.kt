package com.example.akkaactormodel.number

import org.springframework.stereotype.Service
import java.math.BigInteger
import java.time.Duration
import java.util.*
import java.util.concurrent.ExecutorService
import java.util.concurrent.Executors
import java.util.concurrent.TimeUnit
import kotlin.concurrent.thread

@Service
class MultiThreadedPrimeGenerator {
    val workerPool: ExecutorService = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors())
    fun generatePrimeNumbers(count: Int): SortedSet<BigInteger> = TreeSet<BigInteger>().also { primes ->
        val tasks = repeat(count) {
            workerPool.submit {
                val bigNumber = BigInteger(1200, Random())
                primes.add(bigNumber.nextProbablePrime())
                print(".")
            }
        }
        workerPool.awaitTermination(10, TimeUnit.SECONDS)
    }
}