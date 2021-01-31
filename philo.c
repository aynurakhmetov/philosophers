#include "philo.h"

t_time	get_time(void)//функция для получения времени в миллисекундах
{
	struct timeval	t;//структурае timeval

	gettimeofday(&t, NULL);// записывает в структуру t время в секундах и микросекунд прошедших с прошлой секунды
	return ((t_time)(t.tv_sec * 1000 + t.tv_usec / 1000));//время с начала время в миллисекундах
}

void	skip_time(t_time end)//время для пропуска времени для поесть или поспать, нужна так как usleep с большими значениями перескакивается время
{
	// while (get_time() < end)//нынешнее время сравнивается с необходимым и если нынешнее время становиться больше, то цикл прекращается
	// 	usleep(100);//нужен, чтобы не нагружать процессор постоныыми циклами
	usleep(end - get_time());
}

int		print(t_philo *philo, int num)//функция для вывода сообщений философов
{
	pthread_mutex_lock(&philo->mutex->m_print);//блокируем мьютекс вывода, чтобы другие философы ничего не выводили в тот же момент
	philo->now = get_time();//получение нынешнего времени
	if (num == 0 && philo->live)//если num = 0, т.е. флаг взятие вилки и philo->live - никто не умер, а значит можно выводить
		printf("%lld %lld take fork\n", philo->now - philo->start, philo->num);
	if (num == 1 && philo->live)//если num = 1, т.е. флаг еды и philo->live - никто не умер, а значит можно выводить
		printf("%lld %lld eat\n", philo->now - philo->start, philo->num);
	if (num == 2 && philo->live)//если num = 0, т.е. флаг сна и philo->live - никто не умер, а значит можно выводить
		printf("%lld %lld sleep\n", philo->now - philo->start, philo->num);
	if (num == 3 && philo->live)//если num = 0, т.е. флаг раздумий и philo->live - никто не умер, а значит можно выводить
		printf("%lld %lld think\n", philo->now - philo->start, philo->num);
	if (num == 4 && philo->live)//если num = 0, т.е. флаг смерти и philo->live - никто пока не умер(но судя по флагу сейчас умрет), а значит можно выводить
		return (printf("%lld %lld death\n", philo->now - philo->start, philo->num));
	if (num != 4)//если флаг смерти, то не надо разблокировать мьютекс вывода, чтобы никто не мог ничего выводить
		pthread_mutex_unlock(&philo->mutex->m_print);//разблокировать мьютекс вывода, чтобы другие философы сообщали свои состояния
	return (0);//просто ноль
}

void	*death(void *arg)//функция отслеживающая момент смерти философа
{
	t_philo		*philo;//структура философа, смотреть в хедере
	int			check;//флаг того, что мьютекс еды философа был разблокирован

	philo = (t_philo*)arg;//преобразование из void в  t_philo
	check = 0;//мьютекс еды философа не был разблокирован
	while (philo->live)//цикл пока филосов жив
	{
		if (philo->eating + philo->time_to_live <= get_time())//philo->eating - время когда филосов начал есть, philo->time_to_live - время жизни философа, get_time() - нынешнее время, филосов должен умереть если с момента еду пройдет  достаточное время
		{
			print(philo, 4);//вывод сообщения о смерти
			pthread_mutex_unlock(&philo->mutex->m_death);//разблокировка мьютекса смерти, теперь philo->live всех философов станет = 0
			skip_time(get_time() + philo->num_all);//пропустить время равное количеству философов
			pthread_mutex_unlock(&philo->mutex->m_print);//разблокировать мьютекс вывода, теперь снова можно выводить сообщения, но т.к. philo->live = 0, то нельзя
		}
		else if (philo->count >= philo->count_eat && philo->count_eat > 0 && !check)//проверяется что филосов поед достаточное количесвто раз, что аргумент еды указан и что мьютекс не был разблокирован, если все это так, то
		{
			pthread_mutex_unlock(&philo->mutex->m_eat[philo->num - 1]);//разблокировать мьютекс еды
			check = 1;//
		}
		usleep(250);//
	}
	if (philo->count_eat > 0 && !check)//
		pthread_mutex_unlock(&philo->mutex->m_eat[philo->num - 1]);//
	return (NULL);//в функции ниже все отлично описано
}

void	*stop(void *arg)//
{
	t_philo		*philo;//

	philo = (t_philo*)arg;//
	pthread_mutex_lock(&philo->mutex->m_death);//
	philo->live = 0;//
	pthread_mutex_unlock(&philo->mutex->m_death);//
	return (NULL);//читайте в функции eating, там все написано
}

int		doing(t_philo *philo, int num)//
{
	(num == 1 && !pthread_mutex_lock(&philo->mutex->m_fork[philo->left])) ? print(philo, 0) : 0;//
	(num == 1 && !pthread_mutex_lock(&philo->mutex->m_fork[philo->right])) ? print(philo, 0) : 0;//
	if (num == 1 && ++philo->count)//
		philo->eating = get_time();//
	print(philo, num);//
	skip_time(philo->now + philo->skip[num]);//
	if (num == 1 && !pthread_mutex_unlock(&philo->mutex->m_fork[philo->left]))//
		pthread_mutex_unlock(&philo->mutex->m_fork[philo->right]);//
	return (0);//просто ноль, хочу и возвращаю
}

void	*phil(void *arg)//
{
	t_philo		*philo;//
	int			i;//

	philo = (t_philo*)arg;//
	(philo->num % 2) ? usleep(philo->eat_time * 1000) : 0;//
	(philo->num % 2 && philo->num == philo->num_all) ? usleep(philo->sleep_time * 500) : 0;//
	pthread_create(&philo->p_death, NULL, death, (void *)philo);//
	pthread_create(&philo->p_stop, NULL, stop, (void *)philo);//
	while (philo->live)//
	{
		i = 0;//
		while (++i < 4)//
			doing(philo, i);//
	}
	pthread_join(philo->p_death, NULL);//
	pthread_join(philo->p_stop, NULL);//
	return (NULL);//читайте в функции ниже, там все написано
}

void	*eating(void *arg)//
{
	t_philo		*philo;//
	int			i;//

	philo = (t_philo*)arg;//
	i = 0;//
	while (i < philo->num_all)//
		pthread_mutex_lock(&philo->mutex->m_eat[i++]);//
	pthread_mutex_unlock(&philo->mutex->m_death);//
	return (NULL);//потоки всегда возвращают NULL (хотя это ни так, они могут вернуть и не NULL, но здесь вы такое не найдете)
}

/*====================================================================================================================================*/
/*==============================================================> INIT <==============================================================*/
/*====================================================================================================================================*/

int		free_all(t_mutex *mutex, t_data *data)//удаление мьютексов и очищение выделенной пам]ти под массивы мьютексов
{
	t_time	i;//счетчик количества вилок и еды
	int		n;//счетчик количества мьютексов

	i = -1;
	n = 0;
	if (mutex->mut_count > n++)//если количество инициализированных мьютексов больше 0, то уничтожается мьютекс смерти
		pthread_mutex_destroy(&mutex->m_death);
	if (mutex->mut_count > n++)//если количество инициализированных мьютексов больше 1, то уничтожается мьютекс вывода
		pthread_mutex_destroy(&mutex->m_print);
	while (++i < data->args[0])//пока не пройдемся до конца массивов вилок и еды
	{
		if (mutex->mut_count > n++)//если количество инициализированных мьютексов больше 2, 4, 6 и т.д., то уничтожаем мьютекс вилки
			pthread_mutex_destroy(&mutex->m_fork[i]);
		if (mutex->mut_count > n++)//если количество инициализированных мьютексов больше 3, 5, 7 и т.д., то уничтожаем мьютекс еды
			pthread_mutex_destroy(&mutex->m_eat[i]);
		i++;
	}
	if (mutex->m_fork)//если маллок выделил память, то очисщаем ее
		free(mutex->m_fork);
	if (mutex->m_eat)//если маллок выделил память, то очисщаем ее
		free(mutex->m_eat);
	return (1);//вы все еще читаете комментарии после return?
}

int		free_philo(t_philo *philo, pthread_t *pid, int ret)//очищшение массивов потоков и мьютеуосв
{
	if (philo)//сами поймете
		free(philo);//сами поймете
	if (pid)//сами поймете
		free(pid);//сами поймете
	return (ret);//а вот и оно
}

int		init_philo(t_data *data, t_mutex *mut)//функция аллоцированиея массива философов и инициализация потоков философов
{
	t_philo		*philo;//смотреть хедер
	pthread_t	*pid;//массив итендификаторов потоков, вроде  pid_t для процессов
	t_time		i;//счетчик запущенных потоков
	int			ret;//возвращаемое значение, либо 0 - ок, либо 1 - ко

	pid = NULL;//зануляем массив потоков

	if (!(philo = malloc(sizeof(t_philo) * data->args[0])) ||
	!(pid = malloc(sizeof(pthread_t) * (data->args[0] + 1))))//понятно
		return (free_philo(philo, pid, 1));//ошибка
	i = -1;//зануляем счетчик потоков
	ret = 0;//возвращаем почто 0
	while (++i < data->args[0])//идем по количеству философов
	{
		philo[i].num_all = data->args[0];//количество философов
		philo[i].time_to_live = data->args[1];//время жизни одного филосова
		philo[i].eat_time = data->args[2];//время еды одного филосова
		philo[i].sleep_time = data->args[3];//время сна одного филосова
		philo[i].count_eat = data->args[4];//количесвто раз которые КАЖДЫЙ филосов должен поесть( если не указан, то равен -1)
		philo[i].skip[0] = 0;//нифига не делает
		philo[i].skip[1] = data->args[2];//время еды одного филосова
		philo[i].skip[2] = data->args[3];//время сна одного филосова
		philo[i].skip[3] = 0;//время размышлений одного философа = 0
		philo[i].mutex = mut;//указатель на структуру мьютексов
		philo[i].num = i + 1;//номер философа, + 1, т.к. номера начинаются с 1, а не с 0
		philo[i].count = 0;//количсество раз которые он поел
		philo[i].live = 1;//переключатель жизни философа, если = 1, значит жив и продолжает есть, спать и думать, если = 0, значит мертв и не может ничего печатать, уникален для каждого философа
		philo[i].left = i;//номер левой вилки = номер философа - 1, уникален для каждого философа
		philo[i].right = (i + 1 < philo[i].num_all) ? i + 1 : 0;//номер левой вилки = номер философа или 0 для последнего философа, уникален для каждого философа
		philo[i].now = get_time();//нынешнее время, обновляется перед каждым выводом, уникален для каждого философа
		philo[i].start = philo[i].now;//стартовое время, устанавливается в начале программы, уникален для каждого философа
		philo[i].eating = philo[i].start;//время в которое филосов начал есть, необходимо для отслеживание того, должен ли философ умереть, уникален для каждого философа
		if (pthread_create(&pid[i], NULL, phil, (void*)&philo[i]))//создается поток философа. если все ок, то возвращается 0
			break ;//прекратить цикл если не удалось проинициализировать поток
	}
	if (philo->count_eat > 0 && !pthread_create(&pid[i], NULL, eating, (void*)&philo[0]))//если казан дополнительный аргумент в мэйне, то создается поток еды
		i++;//увеличивает счесчик потоков, чтобы в итоге очищать все
	if ((i < data->args[0] || (philo->count_eat > 0 && i == data->args[0])) && (ret = 1))//проверка на ошибки при инициализации потоков
		pthread_mutex_unlock(&mut->m_death);//открываем мьтекс смерти и все запущенные потоки умирают
	while (--i > -1)//идем по всем потокам и присоединяем их к основному процессу
		pthread_join(pid[i], NULL);//присоединяет потоки к родительскому процессу, проще говоря работает подобко waitpid для процессов
	return (free_philo(philo, pid, ret));//сотррите, что возвращает free_philo
}

int		get_mutex(t_mutex *mut, t_data *data)//функция которая инициализирует мьютексы и выделяет память для массиво мьютексов
{
	t_time	i;//счетчик для инициализации вилок и еды

	i = 0;//зануление счетчика для инициализации вилок и еды
	mut->mut_count = 0;//зануление счетчика мьютексов, смотрите в хедере, в структуре mutex
	mut->m_eat = NULL;//зануление указателя m_eat, чтобы не фришить лишнего в случае ошибки
	if (!(mut->m_fork = malloc(sizeof(pthread_mutex_t) * data->args[0])))//выделение памяти на массив мьютексов вилок
		return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
	if (!(mut->m_eat = malloc(sizeof(pthread_mutex_t) * data->args[1])))//выделение памяти на массив мьютексов еды
		return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
	if (pthread_mutex_init(&mut->m_death, NULL) && ++mut->mut_count)//инициализация мьютекса смерти
		return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
	pthread_mutex_lock(&mut->m_death);//закрываем мьютекс death, чтобы открыть когда кто-то из философов умрет или все философы поедят достаточное количество раз
	if (pthread_mutex_init(&mut->m_print, NULL) && ++mut->mut_count)//инициализация мьютекса вывода
		return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
	while (i < data->args[0])//цикл по всем философам
	{
		if (pthread_mutex_init(&mut->m_fork[i], NULL) && ++mut->mut_count)//инициализация одного из мьютексов вилок
			return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
		if (pthread_mutex_init(&mut->m_eat[i], NULL) && ++mut->mut_count)//инициализация одного из мьютексов еды
			return (free_all(mut, data));//в случае ошибки оичщаем все мьютексы
		pthread_mutex_lock(&mut->m_eat[i]);//закрываем каждый мьютекс еды, чтобы открыть когда кто-то из философов поест достаточное количество раз
		i++;//переходим к следующим мьютексам
	}
	return (0);//вы издеваетесь?
}


int		get_args(t_data *data, int argc, char **argv)//функция которая парсит аргументы и записывает в data их числовые значения
{
	int		i;//счетчик строк
	int		j;//счетик символов

	i = 1;//начинаем с первой строки, т.к. нулевая это название нашей программы
	if (argc < 5 || argc > 6)//мы принимает только 4 или 5 аргументов, но если их 4, то argc = 5, а если их 5, то argc = 6
		return (1);//возвращается ошибка
	data->args[4] = -1;//изначально необязательный аргумент (количество раз поесть) приравниваем -1 (поэтому нельзя t_time делать unsigned, иначе все плохо кончится)
	while (i < argc && i < 6)//идем по количеству ргусентов и до 6, зачем до 6? Не помню
	{
		j = 0;//начинаем отсчет с 0 символа строки, т.к. это ее начало
		data->args[i - 1] = 0;//зануляем значение аргумента, который будем считывать
		while (argv[i][j] == ' ' || argv[i][j] == '\t' || argv[i][j] == '\r'
		|| argv[i][j] == '\v' || argv[i][j] == '\n')//скипаем пробелы
			j++;//скипаем пробелы
		while (argv[i][j] >= '0' && argv[i][j] <= '9')//проверяем, что у нас символ цифры
			data->args[i - 1] = data->args[i - 1] * 10 + argv[i][j++] - '0';//магия
		if (j == 0 || argv[i][j])//проверка на пустую строку и наличие лишних символов, еще надо добавить проверку на строку состоящую из пробелов, но мне лень
			return (1);//возврат ошибки
		i++;//переходим к следующей строке
	}
	return (0);//сами разберетесь
}

int		main(int argc, char **argv)
{
	t_data	data;//смотреть в хедере
	t_mutex	mutex;//смотреть в хедере

	if (get_args(&data, argc, argv) || get_mutex(&mutex, &data))//get_args - функция которая парсит аргументы и записывает в data их числовые значения, get_mutex - функция которая инициализирует мьютексы и выделяет память для массиво мьютексов
		return ((write(2, "Error args!\n", 12) && 0) + 1);//Догадайтесь, что это
	init_philo(&data, &mutex);//аллоцированиея массива философов и инициализация потоков философов
	free_all(&mutex, &data);//очистка структуры мьютексов, а data там нужна
	return (0);//Надеюсь сами разберетесь
}