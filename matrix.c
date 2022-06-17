// Vinicius Freitas     20210026803
// Natanael Neto        20190038391
#include "matrix.h"

Matrix create_matrix(int *data, int n_rows, int n_cols){
    Matrix matriz;
    matriz.data = data;
    matriz.n_rows = n_rows;
    matriz.n_cols = n_cols;
    matriz.stride_rows = n_cols;
    matriz.stride_cols = 1;
    matriz.offset = 0;

    return matriz;
}

Matrix zeros_matrix(int n_rows, int n_cols){

    int *p = malloc(n_rows * n_cols * sizeof(int));

    int size = n_rows * n_cols;
    for(int i = 0; i < size; i++){
        p[i] = 0;
    }

    return create_matrix(p, n_rows, n_cols);
}

Matrix full_matrix(int n_rows, int n_cols, int value){

    int *p = malloc(n_rows * n_cols * sizeof(int));

    int size = n_rows * n_cols;
    for(int i = 0; i < size; i++){
        p[i] = value;
    }

    return create_matrix(p , n_rows, n_cols);
}

Matrix i_matrix(int n){

    int *p = malloc(n * n * sizeof(int));

    int size = n * n;
    for(int i = 0; i < size; i++){
        p[i] = 0;
    }
    int count = 0;
    p[0] = 1;
    for(int i = 0; i < size; i++){
        count++;
        if(count == n+1){
            count = 0;
           p[i+1] = 1;
        }
    }

    return create_matrix(p, n, n);
}

Matrix tile_matrix(Matrix matrix, int reps){

    int *p = malloc(sizeof(int) * matrix.n_rows * matrix.n_cols * reps);


    int size = matrix.n_rows * (matrix.n_cols * reps);

    int condition = 0;
    int aux = 0;
    int count = 0;

    for(int i = 0; i < size; i++){
        p[i] = matrix.data[aux + count];
        aux++;
        condition++;
        if(aux == matrix.stride_rows){
            aux = 0;
            if(condition == (matrix.stride_rows * reps)){
                count += matrix.stride_rows;
                condition = 0;
            }
        }
    }

    return create_matrix(p, matrix.n_rows, (matrix.n_cols * reps));
}

int get_element(Matrix matrix, int ri, int ci){
    if(ri >= matrix.n_rows){
        printf("Index out of range.");
        return 0;
    }
    if(ci >= matrix.n_cols){
        printf("Index out of range.");
        return 0;
    }else{
        int element = matrix.data[((ri * matrix.n_cols) + ci)];

        return element;
    }
}

void put_element(Matrix matrix, int ri, int ci, int elem){
    if(ri >= matrix.n_rows){
        printf("Index out of range.");
        return 0;
    }
    if(ci >= matrix.n_cols){
        printf("Index out of range.");
        return 0;
    }else{
        matrix.data[((ri * matrix.n_cols) + ci)] = elem;
    }
}

void print_matrix(Matrix matrix){
    int size = matrix.n_rows * matrix.n_cols;
    int column = 0;
    for(int i = 0; i < size; i++){
        column++;
        if(matrix.data[i] >= 10 || matrix.data[i] < 0){
            printf("%d ", matrix.data[i]);
        }
        else{
            printf("%d  ", matrix.data[i]);
        }
        if(column == matrix.stride_rows){
            column = 0;
            printf("\n");
        }
    }
}

Matrix transpose(Matrix matrix){

    int size = matrix.n_cols * matrix.n_rows;
    int *p = malloc(sizeof(int) * size);

    int aux = 0;
    int proximo = 0;
    for(int i = 0; i < size; i++){
        p[aux] = matrix.data[i];  
        if(aux >= (size - matrix.n_rows)){
            proximo++;  
            aux = proximo;
        }else{
            aux += matrix.n_rows;
        }
         
    }

    return create_matrix(p, matrix.n_cols, matrix.n_rows);
}

Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){
    int size = matrix.n_rows * matrix.n_cols;
    if((new_n_rows * new_n_cols) > size){
        printf("Reshape failed, you are trying to reshape the original matrix into a larger one.\n");
    }
    else{
        matrix.n_rows = new_n_rows;
        matrix.n_cols = new_n_cols;
        matrix.stride_rows = matrix.n_cols;
        matrix.stride_cols = 1;
    }

    return matrix;
}

int min(Matrix matrix){
    int size = matrix.n_rows * matrix.n_cols;
    int min_value = 99999;
    for(int i = 0; i < size; i++){
        if (matrix.data[i] < min_value){
            min_value = matrix.data[i];
        }
    }

    return min_value;
}

int max(Matrix matrix){
    int size = matrix.n_rows * matrix.n_cols;
    int max_value = -99999;
    for(int i = 0; i < size; i++){
        if (matrix.data[i] > max_value){
            max_value = matrix.data[i];
        }
    }

    return max_value;
}

int argmin(Matrix matrix){
    int size = matrix.n_rows * matrix.n_cols;
    int min_value = 99999;
    for(int i = 0; i < size; i++){
        if (matrix.data[i] < min_value){
            min_value = i;
        }
    }

    return min_value;
}

int argmax(Matrix matrix){
    int size = matrix.n_rows * matrix.n_cols;
    int max_value = -99999;
    for(int i = 0; i < size; i++){
        if (matrix.data[i] > max_value){
            max_value = i;
        }
    }

    return max_value;
}

Matrix add(Matrix matrix_1, Matrix matrix_2){

    int *p = malloc(sizeof(int) * matrix_1.n_rows * matrix_1.n_cols);

    int size = matrix_1.n_rows * matrix_1.n_cols;
    for(int i = 0; i < size; i++){
        p[i] = matrix_1.data[i] + matrix_2.data[i];
    }

    return create_matrix(p, matrix_1.n_rows, matrix_1.n_cols);
}

Matrix sub(Matrix matrix_1, Matrix matrix_2){

    int *p = malloc(sizeof(int) * matrix_1.n_rows * matrix_1.n_cols);
    
    int size = matrix_1.n_rows * matrix_1.n_cols;
    for(int i = 0; i < size; i++){
        p[i] = matrix_1.data[i] - matrix_2.data[i];
    }

    return create_matrix(p, matrix_1.n_rows, matrix_1.n_cols);
}

Matrix division(Matrix matrix_1, Matrix matrix_2){

    int *p = malloc(sizeof(int) * matrix_1.n_rows * matrix_1.n_cols);

    int size = matrix_1.n_rows * matrix_1.n_cols;
    for(int i = 0; i < size; i++){
        p[i] = matrix_1.data[i] / matrix_2.data[i];
    }

    return create_matrix(p, matrix_1.n_rows, matrix_1.n_cols);
}

Matrix mul(Matrix matrix_1, Matrix matrix_2){

    int *p = malloc(sizeof(int) * matrix_1.n_rows * matrix_1.n_cols);

    int size = matrix_1.n_rows * matrix_1.n_cols;
    for(int i = 0; i < size; i++){
        p[i] = matrix_1.data[i] * matrix_2.data[i];
    }

    return create_matrix(p, matrix_1.n_rows, matrix_1.n_cols);
}

Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
    int *p = malloc(sizeof(int) * 4);
    Matrix matriz_slice;
    matriz_slice.data = p;
    matriz_slice.n_cols = 2;
    matriz_slice.n_rows = 2;
    matriz_slice.offset = 0;
    matriz_slice.stride_cols = 1;
    matriz_slice.stride_rows = matriz_slice.n_cols;
    int linha_c = 0;
    int linha_f = 0;
    int col_c = 0;
    int col_f = 0;
    if(rs == 0){
        linha_c = 0;
    }else{
        for(int i = 0; i < rs; i++){
            linha_c+=a_matrix.n_cols;
        }
    }
    if(re == 0){
        linha_f = 0;
    }else{
        for(int i = 0; i < re-1; i++){
            linha_f+=a_matrix.n_cols;
        }
    }
    if(cs == 0){
        col_c = 0;
    }else{
        for(int i = 0; i < cs; i++){
            col_c += 1;
        }
    }
    if(ce == 0){
        col_f = 0;
    }else{
        for(int i = 0; i < ce-1; i++){
            col_f+=1;
        }
    }

 
  
    int soma = linha_c + col_c;
    int soma2 = linha_c + col_f;
    int soma3 = linha_f + col_c;
    int soma4 = linha_f + col_f;

    

    matriz_slice.data[0] = a_matrix.data[soma];
    matriz_slice.data[1] = a_matrix.data[soma2];
    matriz_slice.data[2] = a_matrix.data[soma3];
    matriz_slice.data[3] = a_matrix.data[soma4];

    return matriz_slice;
}
