
import random
import numpy  as np
import pandas as pd

from datetime import datetime

from gensim.test.utils import get_tmpfile
from gensim.models import KeyedVectors

df = pd.DataFrame(columns=['Algoritmo', 'Modelo', 'Dimensao', 'Ordenacao Sinonimos', 'Ordenacao Tentativas', 'Palavra Secreta', 'Sinonimos', 'Sinonimo', 'Tentativas', 'Acerto', 'Tipo Acerto', 'Tempo'])

algoritmo = []
algoritmo.append('fasttext')
algoritmo.append('word2vec')
algoritmo.append('wang2vec')
algoritmo.append('glove')

dim = []
dim.append('50')
dim.append('100')
dim.append('300')
dim.append('600')
# dim.append('1000')

top_simil_secret  = 100
top_simil_synonyn = 100

_cont = 0
for _alg in algoritmo:
	
	modelo = []
	if (_alg == 'fasttext' or _alg == 'word2vec' or _alg == 'wang2vec'):
		modelo.append('cbow')
		modelo.append('skip')
	else:
		modelo.append('glove')
#	if (_alg == 'fasttext' or _alg == 'word2vec'):
#		modelo.append('skip')	
#	elif (_alg == 'wang2vec'):
#		modelo.append('cbow')	
#		modelo.append('skip')	
#	else:
#		modelo.append('glove')
		
	for _mod in modelo:
		
		for _dim in dim:
			
			ini = datetime.now()
			
			filepath = '/home/nilc_embeddings/'
			filename_txt   = filepath + _alg + "/" + _mod + "_s" + _dim + ".txt"
			filename_model = filepath + _alg + "/" + _mod + "_s" + _dim + ".model"
			
			conhecedor = KeyedVectors.load_word2vec_format(filename_txt, encoding='utf8')
			advinhador = KeyedVectors.load_word2vec_format(filename_txt, encoding='utf8')
			fname = get_tmpfile(filename_model)
			conhecedor.save(fname) # conhecedor.wv.save(fname) # Funciona do mesmo jeito
		##	conhecedor.wv.save_word2vec_format(fname)	
			
		#	conhecedor = KeyedVectors.load(filename_model, mmap='r')
		#	advinhador = KeyedVectors.load(filename_model, mmap='r')
			
			vocab = []
			f = open(filename_txt)
			for line in f:
				if(line.strip() != ''): 
					cols = [j.strip() for j in line.split(' ')] 
					vocab.append(cols[0])
			f.close()
			
			num_verbetes = int(vocab[0])
			
			print(num_verbetes)
			
			np.random.seed(_cont+9999)
			secret_num  = np.random.random_integers(1,num_verbetes)
			secret_word = vocab[secret_num].decode("utf-8")
			
			print(secret_word)
			
			secret_more = conhecedor.most_similar(positive=secret_word, negative=None, topn=top_simil_secret, restrict_vocab=None, indexer=None)
			secret_less = list(reversed(secret_more))
			secret_rand = list(secret_more)
			random.shuffle(secret_rand)
			
#			1. ['More'] + ['More']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_more[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1
			
#			2. ['More'] + ['Less']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_more[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				senha = list(reversed(senha))
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1			
			
#			3. ['More'] + ['Rand']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_more[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				random.shuffle(senha)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['More'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1			
			
#			4. ['Less'] + ['More']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_less[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1		
			
#			5. ['Less'] + ['Less']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_less[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				senha = list(reversed(senha))
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1				
			
#			6. ['Less'] + ['Rand']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_less[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				random.shuffle(senha)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Less'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1			
			
#			7. ['Rand'] + ['More']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_rand[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['More'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1				
			
#			8. ['Rand'] + ['Less']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_rand[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				senha = list(reversed(senha))
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['Less'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1

#			9. ['Rand'] + ['Rand']
			achou = False
			hit = [-1,-1]
			for i in range(top_simil_secret):
				senha = advinhador.most_similar(positive=secret_rand[i][0], negative=None, topn=top_simil_synonyn, restrict_vocab=None, indexer=None)
				random.shuffle(senha)
				for j in range(top_simil_synonyn):
					if (senha[j][0] == secret_word):
						hit = [i,j]
						if (not achou):
							fim = datetime.now()
							tempo = fim - ini
							df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Primeiro'] + [tempo]
							_cont += 1
							achou = True
						break
			fim = datetime.now()
			tempo = fim - ini
			df.loc[_cont] = [_alg] + [_mod] + [_dim] + ['Rand'] + ['Rand'] + [secret_word] + [secret_more] + [secret_more[i][0]] + [senha] + [hit] + ['Ultimo'] + [tempo]
			_cont += 1				
			
			df.to_csv("megasenha_resultado.csv", index=False, encoding='utf8')
			
			print(df)
			
			
# conhecedor: sorteia 1 palavra e extrai 5 sinonimos.
# conhecedor: informa do 1o ao 5o sinonimo para o advinhador na ordem do mais similar ao menos similar e depois vice-versa.
# advinhador: a cada sinonimo informado, calcula (tenta advinhar) a palavra secreta.
# Sao 3 modos:
# 1. Comparacao de secret_word com os varios sinonimos recuperados pelo advinhador para 1 UNICO sinonimo da secret_word.
# 2. Comparacao de secret_word com os sinonimos recuperados iteradamente pelo advinhador para cada um dos 5 sinonimos da secret_word.
# 3. Comparacao de secret_word com os varios sinonimos recuperados pelo advinhador para cada um dos 5 sinonimos da secret_word, de forma iterada.