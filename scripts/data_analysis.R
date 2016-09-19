#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

library(ggplot2)
df<- read.csv(file=args[1],head=TRUE,sep=",")
ggplot() +
geom_line(data=df, aes(x = x, y = y, group = data) ) 

ggsave(file=args[2])

