#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)

library(ggplot2)
df<- read.csv(file=args[1],head=TRUE,sep=",")
ggplot() +
geom_line(data=df, aes(x = x, y = y, colour = data) ) +
theme(legend.position="bottom", legend.text=element_text(size=15))

ggsave(file=args[2])

