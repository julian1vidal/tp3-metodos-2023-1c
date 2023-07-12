
all: 
	g++ jacobi_sum.cpp -o jacobi_sum -O3 -std=c++17
	g++ jacobi_mat.cpp -o jacobi_mat -O3 -std=c++17
	g++ gs_sum.cpp -o gs_sum -O3 -std=c++17
	g++ gs_mat.cpp -o gs_mat -O3 -std=c++17
	g++ main.cpp -o main -O3 -std=c++17

jacobi_sum:
	g++ jacobi_sum.cpp -o jacobi_sum -std=c++17

jacobi_mat:
	g++ jacobi_mat.cpp -o jacobi_mat -std=c++17

gs_sum:
	g++ gs_sum.cpp -o gs_sum -std=c++17

gs_mat:
	g++ gs_mat.cpp -o gs_mat -std=c++17

clean_entrys:
	rm ./salida.txt
	rm ./entrada.txt
	rm ./errors.txt
	rm ./tiempos.txt

clean:
	rm ./jacobi_mat
	rm ./jacobi_sum
	rm ./gs_mat
	rm ./gs_sum
	rm ./main