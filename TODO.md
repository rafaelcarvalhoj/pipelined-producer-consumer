# Pendências

## Execução da pipeline

- [ ] Implementar `phase1_run`: distribuir os `M` itens entre as threads de E1, gerar identificadores únicos e depositar cada item em B1. Se a falha de B1 começar depois que um item for gerado, mantê-lo para depósito após a recuperação.
- [ ] Implementar `phase2_run`: retirar itens de B1, transformar o conteúdo e depositá-los em B2. Uma thread que já retirou um item antes da falha de B1 deve concluir o processamento e depositá-lo em B2.
- [ ] Implementar `phase3_run`: retirar itens de B2, registrar o consumo final e aguardar quando B2 estiver vazio, inclusive durante a falha de B1.
- [ ] Definir e implementar o protocolo de término dos estágios e buffers. E3 deve encerrar somente depois que E2 terminar e B2 estiver vazio. Threads bloqueadas em `buffer_put` ou `buffer_get` precisam ser acordadas para que a pipeline possa finalizar sem deadlock.
- [ ] Implementar a interrupção externa de B1 por cinco segundos, o descarte e a contagem dos itens que estavam em B1, e a retomada automática de E1 e E2. E3 deve continuar operando durante a falha.
- [ ] Adicionar a contagem de itens produzidos, consumidos e perdidos, e exibir o relatório final com a verificação de conservação.

## Documentação

- [ ] Preencher a seção 3 do relatório: algoritmo de resolução.
- [ ] Preencher a seção 4 do relatório: conclusão.
- [ ] Preencher a seção 5 do relatório: referências.
