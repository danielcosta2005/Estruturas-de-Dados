# Diretórios
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Arquivos
TARGET = $(BIN_DIR)/tp2.out
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
CXX = g++
CXXFLAGS = -Wall -I$(INCLUDE_DIR)

# Regra principal
all: $(TARGET)

# Regra para gerar o executável
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Regra para compilar os arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
