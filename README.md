# C
estrutura de dados
Você foi contratado pelo seu Joãozin da Bodega para criar um sistema com o qual ele
possa controlar alguns detalhes do seu business. Seu Joãozin já definiu o que é mais
importante, para que você comece a criar a estrutura do sistema para a melhor bodega do sul
do país. Os requisitos são os seguintes
1. Seu programa principal (main) se chamará Bodega.
2. Crie uma estrutura Bebida com os seguintes atributos: código, o nome da bebida
(nome sem espaço), o conteúdo líquido em ml (int), o preço de venda, a quantidade em
estoque e se é alcóolica ou não.
3. A bodega deverá ter obrigatoriamente uma lista de bebidas chamada bebidas. Toda vez
que um cliente ou bebida é criado, deve posteriormente ser adicionado na lista
correspondente.
4. Crie um menu interativo que pergunta ao usuário o que deseja fazer:
4.1. Cadastrar bebida;
4.2. Listar bebidas;
4.3. Buscar bebida;
4.4. Excluir bebida;
4.5. Comprar bebida;
4.6. Vender bebida;
4.7. Sair do sistema;
5. O que acontece em cada item do menu:
5.1. Ao escolher a Opção Cadastrar bebida: Leia valores via teclado e insira na lista
de bebidas. Não são permitidas duas bebidas com o mesmo código.
5.2. Ao escolher a Opção Listar bebidas: Mostre os dados de todas as bebidas.
5.3. Ao escolher a Opção Buscar bebida: Peça um código de bebida e mostre os
dados da bebida que possuir este código. Caso o código não esteja cadastrado
apresentar a mensagem ‘Bebida não cadastrada!’
5.4. Ao escolher a Opção Excluir bebida: Peça um código de bebida e exclua a
bebida que possuir este código.
5.5. Ao escolher a Opção Comprar bebida: Peça um código de bebida para compra e
a quantidade de unidades a serem compradas. Lembre que a bebida já está na
lista, e você deve adicionar unidades em seu estoque.
5.6. Ao escolher a Opção Vender bebida: Peça um código de bebida para venda e a
quantidade de unidades a serem vendidas e se o usuário é maior de 18 anos.
Deve-se verificar se tem estoque de bebida para efetuar a venda, e caso a
bebida seja alcoólica não permitir a venda para usuário que tenham menos de
18 anos.
5.7. Ao escolher a Opção Sair do sistema: Saia do sistema.
