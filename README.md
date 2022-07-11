# Robocross
АННОТАЦИЯ

Проект был создан для участия в РОБОКРОСС 2022 - ежегодные всероссийские испытания беспилотного транспорта. Проект создан при поддержке Донского государственного технического университета и структурного подразделения Ресурсного Центра Робототехники (РЦР). Работа была начата в октябре 2021 года на серийном автомобиле ВАЗ-1111, а в марте 2022 года университетом был предоставлен серийный автомобиль более нового образца - Лада гранта. Так как автомобиль необходимо собрать, в рамках соревнований, беспилотным, то были проведены следующие работы: автономность поворота электроусилителя руля(ЭУРа), автономность системы нажатия педалей (сцепление, газ, тормоз), автономность механической коробки передач.
______________________________________________________________________________________________________________________________

1. Начало 

Каждому члену нашей команды была отведена задача, которую необходимо реализовать, в рамках подготовки в всероссийским испытаниям беспилотного транспорта.
Мне, как программисту-разработчику нижнего уровня, необходимо было вести проект управления исполнительными элементами автомобиля. В число элементов входил педальный узел(сцепление, тормоз, газ), управление электроусилителем руля, управление механической коробкой передач и передача актуальных данных ЭВМ верхнего уровня.
Испытания проводились на серийном автомобиле Лада Гранта FL учебной комплектации с параллельным педальным узлом.
![CmmQlvBD8uk37-oiVmhUjIeTMFEuv8TjOS72Y_4P4vU-f_4QHIoWXfCxOsIcmFV7m69jP-LEAnb2WX9gmhC8HsLO](https://user-images.githubusercontent.com/91759086/178328498-c113d7da-5a7d-46d6-baa2-a3d285c33250.jpg)

С марта 2022 года была начата работа с электроусилителем руля. Использование стандартного блока управления накладывало множество трудностей с управлением в связи с тем, что ЭБУ автомобиля от подмены данных постоянно переходил в защищенное состояние с ошибкой, поэтому в рамках подготовки к соревнованиям было принято решение приостановить идею с таким типом управления. Был использован самодельный драйвер бесколекторного двигателя. Плата с наработки по программному обеспечению были предоставлены сотрудником дружественной лаборатории НИЛ ИЭСМиК Назаренко Дмитрием Владимировичем, за что я выражаю отдельную благодарность. В связи с договоренностью о нераспространении ПО рулевого управления, в данном проекте отсутстует программный код управления, только изображение стенда, на котором отлаживалась работа с электоуслителем руля. Принцип управления отталкивался от встроенных в двигатель двух датчиков холла. Получая с них данные, они преобразовывались в электрический угол рулевой рейки и подавались на вход ПИ-регулятора положения, для отработки заданного целевого угла поворота.

![image](https://user-images.githubusercontent.com/91759086/178329387-0888fb21-c78e-41d0-86f8-4fc4bb16544f.png)

2. Обмен данными с ЭВМ верхнего уровня

С конца мая началась работа по проектированию и написанию алгоритма управления остальными системами автомобиля. Первой нерешенной задачей было обеспечение обмена данными между ЭВМ и двумя периферийными устройствами: электроусилитель руля на контроллере dsPIC32EP64 и платой управления остальными системами на контроллере STM32F407. Для первичного проектирования был выбран протокол ModBus ASCII как наиболее удобный и наглядно показывающий структуру присылаемых данных. Код 0х06 предназначался для записи целевых значений, присылаемых с ПК, код на чтение 0х03 был предусмотрен, но впоследствии было принято решение сделать просто периодическую отправку текущего состояния в связи с загруженностью разработчика ПО верхнего уровня.

3. Управление механической коробкой передач

Управление КПП было реализовано через управление двумя двигателями постоянного тока. Так как, механика реализована ременной системой Core XY, то необходимым условием работы было поддержание одинаковой скорости двигателей. Был учтен тот факт, что даже одинаковые двигатели были куплены в один день, то не факт что их выходные характеристики будут идентичными. Поэтому был написан простой ПИД-регулятор скорости, который получал входные данные с угловых энкодеров магнитного типа AS5040. Итоговое управление передачей реализовано матричным способом - в матрице хранились значения направлений, по которым двигался селектор, а ключевыми отметками служили датчики холла. Приведен скриншот модели и изображение как было реализовано механическое исполнение. Управление коробкой передач осуществляется через функцию Set_Transmission(int transmission), тело которой находится в файле Car_Management.c

![image](https://user-images.githubusercontent.com/91759086/178335250-1f2487bd-1f0c-4023-a280-8e5804121554.png)
![image](https://user-images.githubusercontent.com/91759086/178335775-206e5586-5139-4fc2-9813-e9316a437fa1.png)

4. Управление педальным узлом

Комплект педалей инструктора, установленный в комплектации «учебная», состоит из механических педалей тормоза и сцепления. Для управления положением дроссельной заслонки была произведена модификация заводской электронной педали газа. Нажатие на педаль тормоза осуществляется пневмоцилиндром с демпфером  для регулировки скорости выдвижения штока. Бесперебойную работу привода тормозящего механизма обеспечивает пневморессивер, изготовленный из медицинского кислородного баллона, давление в котором поддерживается автомобильным пневматическим компрессором, оснащённым системой контроля давления в подключённом контуре. Компрессор включается автоматически для поддержания рабочего давления в баллоне.

![image](https://user-images.githubusercontent.com/91759086/178336223-675bb1f7-c833-44d2-83ab-7a42889f328f.png)
![image](https://user-images.githubusercontent.com/91759086/178336273-102059bb-6052-4ae2-93da-f08a10bfe1fb.png)
![image](https://user-images.githubusercontent.com/91759086/178336313-75395bad-d8b7-4080-8d60-5c210ea9d341.png)

