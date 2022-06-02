NOME: GUSTAVO ANDRADE DE PAULA
TIA: 42081327

ps:Código foi compilado no replit.com, usando o seguinte comando na chamada de terminal: g++ -pthread main.c -w  -o main && ./main (comando se encontra comentado no código também)

1. A conta to pode receber mais de uma transferência simultânea;

2. A conta from pode enviar mais de uma transferência simultânea;

Ambas operações são possíveis pela simples operação de se criar processos, como é possível observar nessa imagem, enquanto um processo ainda nao terminou de executar, outro já começou sua execução por conta do primeiro ter já acessado o recurso

![image](https://user-images.githubusercontent.com/99684321/171753838-9e4e05ae-3231-4e3c-910f-3136d125f194.png)


3. A conta from não pode enviar dinheiro se não tiver mais saldo;

![image](https://user-images.githubusercontent.com/99684321/171753999-5718a773-b163-4cf0-bc6a-b052552fa482.png)

Como pode ser observado, ao passar pelo else if isso significa que a conta to nao pode mais transferir nada

4. A conta to pode trocar de ordem com a conta from, ou seja, a conta que enviava pode
receber e a conta que recebia pode enviar;

![image](https://user-images.githubusercontent.com/99684321/171754126-9d913b17-1fde-4497-b5da-29e888dd7adc.png)

Como pode ser observado, a se colocar mais de 100 processos para executar, o programa automaticamente irá transferir o proximo valor da conta to para from

5. Poderão ser realizadas até 100 transações simultâneas de transferência.

Como dito nos pontos anteriores, é possível colocar o número de processos desejado graças a essas linhas de código

![image](https://user-images.githubusercontent.com/99684321/171754272-23bc9118-9a1f-43ff-8fdc-2a1e90285b2f.png)
![image](https://user-images.githubusercontent.com/99684321/171754341-a5f27405-24f4-4f0e-86ea-309fef68775a.png)



Fontes:


https://stackoverflow.com/questions/23250863/difference-between-pthread-and-lpthread-while-compiling

https://www.geeksforgeeks.org/use-posix-semaphores-c/

https://www.ibm.com/docs/en/zos/2.1.0?topic=functions-waitpid-wait-specific-child-process-end

https://greenteapress.com/thinkos/html/thinkos013.html#:~:text=A%20semaphore%20is%20a%20data,implement%20Pthreads%20also%20provide%20semaphores.
