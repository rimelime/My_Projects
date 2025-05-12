from random import choice, choices, randrange, random
import time
import matplotlib.pyplot as plt

items = [{"name":"laptop","weight":1.2,"usefullness":600},
         {"name":"phone","weight":0.5,"usefullness":150},
         {"name":"Makeup","weight":0.3,"usefullness":20},
         {"name":"lighter","weight":0.2,"usefullness":500},
         {"name":"flashlight","weight":0.5,"usefullness":600},
         {"name":"snack","weight":0.1,"usefullness":100},
         {"name":"map","weight":0.1,"usefullness":100},
         {"name":"first aid","weight":1.0,"usefullness":500},
         {"name":"spare cloth","weight":0.5,"usefullness":700},
         {"name":"mosquitoe lamb","weight":1.1,"usefullness":500},
         {"name":"mini TV","weight":2.0,"usefullness":1500},
         {"name":"camera","weight":1.0,"usefullness":550},
         {"name":"books","weight":0.5,"usefullness":480},
         {"name":"plant","weight":1.0,"usefullness":720},
         {"name":"poker","weight":0.1,"usefullness":80}]
def make_gene(length):
    return [choice([0,1]) for _ in range (length)]
def make_population(PopNum,genelength):
    return [make_gene(genelength) for _ in range (PopNum)]
def gene_Fitness(items,gene,maxweight):
    if len(items)!=len(gene): return ValueError("invalid gene")
    fitness = 0
    weight = 0
    for i , present in enumerate(gene):
        if present == 0:
            continue
        fitness += items[i]["usefullness"]
        weight += items[i]["weight"]
    if weight > maxweight:
        return 0
    return fitness 
def crosover_func(genea,geneb):
    if len(genea)!=len(geneb): return ValueError("unbalance gene")
    if len(genea)==2: return genea,geneb
    point = int(len(genea)/2)
    return genea[:point]+geneb[point:] , geneb[:point]+genea[point:]
def uniCrossover_func(genea,geneb):
    if len(genea)!=len(geneb): return ValueError("unbalance gene")
    if len(genea)==2: return genea,geneb
    crossover_genea = [genea[i] if i % 2 == 0 else geneb[i] for i in range(len(genea))]
    crossover_geneb = [geneb[i] if i % 2 == 0 else genea[i] for i in range(len(geneb))]
    return crossover_genea , crossover_geneb#genea[:point]+geneb[point:] , geneb[:point]+genea[point:]
def mutate_gene(Gene,time=1,prob=0.2):
    for i in range(time):
        index = randrange(len(Gene))
        Gene[index]=Gene[index] if random() > prob else abs(Gene[index]-1)
    return Gene

def printgene_info(gene,items):
    itemlist= ""
    value = 0
    weight = 0
    for i,bit in enumerate(gene):
        if bit ==1:
            if itemlist=="" : 
                itemlist += items[i]["name"]
            else : 
                itemlist += ', ' + items[i]["name"]
            value += items[i]["usefullness"]
            weight += items[i]["weight"]
    print(f"The list include: {itemlist}. Usefullness scorce: {value}, weight: {weight}")

def select_func(items,population,fit_func,maxweight):
    return choices(
        population=population,
        weights=[fit_func(items,gene,maxweight) for gene in population],
        k=2
    )
def GeneticAlgorthsm(items,max_weight,fitness_func,select_func,cross_func,mutate_func,generation_limit):
    start= time.time()
    while True:
        population = make_population(50,len(items))
        if  any(gene_Fitness(items,gene,max_weight)!=0 for gene in population):
            break
    report1,report2,report3 = [],[],[]
    for i in range(generation_limit):
        population.sort(key=lambda x: gene_Fitness(items,x,max_weight),reverse=True)
        report1.append(gene_Fitness(items,population[0],max_weight))
        report2.append(gene_Fitness(items,population[1],max_weight))
        report3.append(gene_Fitness(items,population[2],max_weight))
        nextpopulation = population[0:2]
        for j in range (int(len(population)/2)-1):
            parents=select_func(items,population,fitness_func,max_weight)
            offstring1,offstring2=cross_func(parents[0],parents[1])
            nextpopulation += [mutate_func(offstring1,prob=0.5),mutate_func(offstring2,prob=0.5)]
        population = nextpopulation
    population.sort(key=lambda x: gene_Fitness(items,x,max_weight),reverse=True)
    report1.append(gene_Fitness(items,population[0],max_weight))
    report2.append(gene_Fitness(items,population[1],max_weight))
    report3.append(gene_Fitness(items,population[2],max_weight))
    end= time.time()
    print(f"The model runtime is: {end-start}")
    return population[:3],report1,report2,report3


solutions,line1,line2,line3=GeneticAlgorthsm(
    items=items,
    max_weight=3,
    fitness_func=gene_Fitness,
    select_func=select_func,
    cross_func=uniCrossover_func,
    mutate_func=mutate_gene,
    generation_limit=100)
for sol in solutions:
    printgene_info(sol,items)
plt.plot(line1,label="best offstring",color="blue")
plt.plot(line2,label="second offstring",color="yellow")
plt.plot(line3,label="best offstring",color="pink")
plt.title("Genetic Progess of the best children")
plt.xlabel("Generation")
plt.ylabel("Score")
plt.legend()
plt.show()
