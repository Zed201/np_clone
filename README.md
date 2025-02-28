 # numpy_clone
Basicamente um clone do numpy criando a classe matrix e algumas funções auxiliares; O objetivo inicial era transpor para Cython mas achei muitos problemas de compatibiliade então deixei em c++ mesmo.

### TODO:
- [X] Corrigir os write invalid que mostra no valgrind
- [X] Corrigir a função dividi2d
- [ ] Implementar normalizaçãp
- [ ] Implementar determinante
- [ ] Implementar inversão de matrizes
- [ ] Implementar autovetores e autovalores
- [X] Erro na divisão
- [ ] Implementar templates(do jeito que esta organizado não da pois gera erro de ld, o compilador não gera as funções necessárias)