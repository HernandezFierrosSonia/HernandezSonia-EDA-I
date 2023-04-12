// Implementacion de una cola doble en C

#include <stdio.h>
#define MAX 10

/*https://youtu.be/n6BEuft6Fq4
https://youtu.be/4fc-QRl8_QQ*/

void enqueueFront(int *, int, int *, int *);
void enqueueRear(int *, int, int *, int *);
int dequeueFront(int *, int *, int *);//devuelve el elemento eliminado
int dequeueRear(int *, int *, int *);//devuelve el elemento eliminado
void display(int *);
int count(int *);

void enqueueFront(int *arr, int item, int *front, int *rear)//en una cola simple o en una cola circular no encolamos en front 
/*nota como un arreglo entero unidimensional se recibe en esta función, se nos envió una dirección
la recibimos como tal, recibimos una dirección como tal, para este caso no le importa a la función saber el tamaño(se puede mandar [tamaño1][tamaño2] o solamente[][tamaño2]).
La cosa cambia en arreglo entero bidimensional, por que ahí a la función si le importa el tamaño, pero la diferencia
es que recibe el arreglo como si fuera entero no como una dirección, pese a que si mandaste una dirección.*/
{
//este queue ingresa para su izquierda
    int i, k, c;

    if(*front==0 && *rear==MAX-1) 
    {
        printf("\nDeque esta llena.\n");
        return;
    }

    if(*front==-1)//también puede ser if(*rear==-1)//es la primera vez que encolamos
    {
        *front=*rear=0;//los dos apuntan al mismo elemento
        arr[*front]=item;
        return;
    }

    if(*rear!=MAX-1)
    {
        c=count(arr);
        k=*rear+1;//rear no va a cambiar
        printf("Cangrejo equivocado: %d\n", c);

        for(i=1; i<=c; i++)//dentro de for no se ocupa i.
        //era más bonito cuando rear==MAX-1 en la función de enqueueRear
        //recorremos el arreglo entero un espacio para adelante, lo recorremos pa' alla->
        {
            arr[k]=arr[k-1];//recorremos espacio por espacio, al final el arreglo entero se recorre SOLO un espacio//el 7 tiene lo de 6, el 6 tiene lo de 5, el  5 tiene lo de 4, ...
            k--;//puedes ahorrarte esta línea poniendo k-- arribita, no creo que pase nada
        }
        arr[k]=item;//k tiene este valor k=k-c, creo que k también valor lo que vale rear
        *front=k;
        (*rear)++;//rear vale un espacio más, por que recorrimos el arreglo entero un espacio
    } 
    else// rear==9
    {
        (*front)--;//front agrega hacia la izquierda
        arr[*front]=item;
    }
}

void enqueueRear(int *arr, int item, int *front, int *rear)//aun me es curioso que recibimos el arreglo como una dirección
//cuando rear mete, si es que aplica primero recorre todo el arreglo un espacio hacia atrás
//enqueue rear siempre agrega hacia la derecha, y nunca rebasa de 9 para pasarse a 0
{
    int i, k;

    if(*front==0 && *rear==MAX-1)//no te confundas, es la mezcla de las dos condiciones lo que ocasiona que este llena, no solo una condición
    {
        printf("\nLa double queue (deque) está llena.\n");
        return;
    }

    if(*front==-1)//es la primera vez que agregamos 
    //creo también podría ser if(*rear==-1)
    //recuerda que como es apuntador, para ver o usar el valor original necesitamos el número de asteriscos original
    {
        *rear=*front=0;//colocamos los dos 
        arr[*rear]=item;
        return;
    }

    if(*rear==MAX-1)//todo lo que veras a continuación es para recorrer el arreglo un lugar hacia atrás, tiene sentido por que no es cola doble circular, que tonta toy
    {
        //eliminé algo oficial aquí
        for(i=(*front-1); i<(MAX-1); i++)//podríamos i=k pero nop se puede//originalmente MAX-1 era *rear
        {
            //eliminé algo oficial aquí
            if(i==MAX-1)//rear ya está ahí, lo sé por el if anterior
            //oie, nunca va a estrar aquí, por que i no llega al valor max-1 es decir 9, llega a uno menos, <9
                arr[i]=0;
            else
                arr[i]=arr[i+1];//no modifica i//recorremos todo el arreglo un espacio pa atrás
                //el 1 tiene lo que tiene el 2, el 2 tiene lo que tiene el 3,...
        }
        (*front)--;//son índices recuerda
    }
    else//cuando rear está en medio, es decir entra cuando no está en los extremos, en espacial este else comprobó que no esta en el extremo más alto
    //este else es similar a else if(*rear!=MAX-1), así lo pusimos en enuqueFront
    {
        (*rear)++;
        arr[*rear]=item;
    }
}

int dequeueFront(int *arr, int *front, int *rear) 
{
    int item;

    if(*front==-1) 
    {
        printf("\nDeque esta vacia.\n");
        return 0;
    }

    item=arr[*front];
    arr[*front]=0;

    if(*front==*rear)
        *front=*rear=-1;
    else
        (*front)++;

    return item;
}

int dequeueRear(int *arr, int *front, int *rear)//en una cola circular o en una cola simple no desencolamos en rear 
{
    int item;

    if(*front==-1)
    {
        printf("\nDeque esta vacía.\n");
        return 0;
    }

    item=arr[*rear];
    arr[*rear]=0;
    (*rear)--;
    if(*rear==-1)
        *front=-1;
    return item;
}

void display(int *arr)
{
    int i;

    printf("\n frente:  ");
    for(i=0; i<MAX; i++)
        printf("  %d", arr[i]);
    printf("  :parte trasera");
}

int count(int *arr)//cuenta cuantos lugares tenemos ocupados
{
    int c=0, i;

    for(i=0; i<MAX; i++)
    {
        if(arr[i]!=0)//a que curioso, es la forma de comprobar que el arreglo no este vacío, pero esto no funciona con tipo de dato char
            //lo que no tiene en cuenta, es qué pasa si el usuario me da 0 como valor para encolarlo
            c++;
    }
    //nota que no tiene nada que ver: después de un for, i si se modificó, siempre y cuando i no este declarada dentro de for, incluso dentro del for la i tiene sus limitacones, no lo hagas
    return c;
}

int main() 
{
    int arreglo[MAX];//10
    int front, rear, i, n;

    front=rear=-1;

    for (i=0; i<MAX; i++)
        arreglo[i]=0;

    enqueueRear(arreglo, 50, &front, &rear);//está primera vez no importa si se usa enqueueRear o enqueueFront//arreglo así como está escrito, es una dirección.
    enqueueFront(arreglo, 120, &front, &rear);
    enqueueRear(arreglo, 110, &front, &rear);
    enqueueFront(arreglo, 50, &front, &rear);
    enqueueRear(arreglo, 60, &front, &rear);
    enqueueFront(arreglo, 80, &front, &rear);

    printf("\nElementos en la doble queue (deque): ");
    display(arreglo);

    i=dequeueFront(arreglo, &front, &rear);//reutilizamos la variable i
    printf("\nElemento eliminado: %d", i);

    printf("\nElementos en la doble queue (deque) después de borrar:");//dequeue es lo mismo que double queue
    display(arreglo);

    enqueueRear(arreglo, 160, &front, &rear);
    enqueueRear(arreglo, 70, &front, &rear);

    printf("\nElementos en la doble queue (deque) despu[es de anadir:");
    display(arreglo);

    i=dequeueRear(arreglo, &front, &rear);
    printf("\nElemento eliminado: %d", i);

    printf("\nElementos en la doble queue (deque) después de eliminar: ");
    display(arreglo);

    n=count(arreglo);
    printf("\nNúmero total de elementos en la doble queue (deque): %d\n", n);
}

/*esta cola es medio confusa, la diferencia con la cola es que con la cola doble
puedes insertar y sacar en front y puedes insertar o sacar en rear
Escensialmente yo no compararía la cola doble con la cola circular*/