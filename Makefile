NAME = main

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17

SRCS = main.cpp \
		arbol.cpp \
		lector_xml.cpp \
		extern/tinyxml2.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Enlazando archivos para crear el ejecutable..."
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "¡Listo! Puedes ejecutar usando ./$(NAME)"

%.o: %.cpp
	@echo "Compilando $< ..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Limpiando archivos objeto temporales ..."
	rm -f $(OBJS)

fclean: clean
	@echo "Limpiando ejecutable ..."
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re