
all: 
	g++ jacobi_sum.cpp -o jacobi_sum -O3
	g++ jacobi_mat.cpp -o jacobi_mat -O3
	g++ gs_sum.cpp -o gs_sum -O3
	g++ gs_mat.cpp -o gs_mat -O3
	g++ main.cpp -o main -O3

jacobi_sum:
	g++ jacobi_sum.cpp -o jacobi_sum

jacobi_mat:
	g++ jacobi_mat.cpp -o jacobi_mat

gs_sum:
	g++ gs_sum.cpp -o gs_sum

gs_mat:
	g++ gs_mat.cpp -o gs_mat

clean_entrys:
	rm ./salida.txt
	rm ./entrada.txt
	rm

clean:
	rm ./jacobi_mat
	rm ./jacobi_sum
	rm ./gs_mat
	rm ./gs_sum
	rm ./main