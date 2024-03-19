#!/bin/bash

tar -cvf ./backup_"$(date +%d-%m-%Y_%H-%M-%S)".tar ./* 2 > /dev/null
