# Definições das variáveis
CC = gcc                  # Compilador
CFLAGS = -Wall -g         # Flags de compilação (exibe todos os avisos e permite depuração)
OBJ = pizza.o ingredientes.o main.o  # Arquivos objeto
EXEC = pizzaria.exe        # Nome do executável

# Regra padrão (executada com `make` ou `make all`)
all: $(EXEC)

# Regra para criar o executável
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Regras para compilar os arquivos .c em .o (arquivos objeto)
pizza.o: pizza.c pizza.h
	$(CC) $(CFLAGS) -c pizza.c -o pizza.o

ingredientes.o: ingredientes.c ingredientes.h
	$(CC) $(CFLAGS) -c ingredientes.c -o ingredientes.o

main.o: main.c pizza.h ingredientes.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Limpar os arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Executar o programa
run: $(EXEC)
	./$(EXEC)
