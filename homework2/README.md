# Команды
add scooter id name energy score - добавить электросамокат, смысл как в задании
add bike id name score - добавить велосипед
add ebike id name energy score - добавить электровелосипед
add roller_skates id name score - добавить ролики
add helmet id name - добавить шлем
add dock id name energy - добавить док-станцию
add roller_skates_gear id name - добавить защиту для роликов
remove id - удалить по id
energy - суммарная энергия в парке (смысл: суточная трата)
max_energy -  максимальная энергия в парке
novice - вывести транспорт для новичков
count_novice - вывести количесвто транспорт для новичков
list - вывести весь транспорт в парке
focus id - выбрать item дня
show_focus - вывести item дня, если он есть, иначе removed (в том числе если не было item дня до этого)
log - вывести все оперции добавления/удаления
log_energy - вывести все операции суммарной энергии (смысл: лог суточных трат)
quit - завершить работу
# Сборка
```
g++ main.cpp Inventory.cpp ServiceCenter.cpp Things.cpp Transport.cpp -o main.out
./main.out
```
# Схема наследования
![[Схема.png]]
InventoryItem, EnergyConsumer, Transport, Thing - абстрактные классы
Transport и Thing наследуются от InventoryItem
Scooter и Ebike наследуются от Transport и EnergyConsumer
Bike и RollerSkates - от Transport 
Dock - Thing и EnergyConsumer
Helmet и RollerSkatesGear - от Thing
Нарисовал схему выше(сверху вниз идет спуск к наследникам, наследников EnergyConsumer выделил синим)
Использовал только multiple inheritance в Scooter, Ebike, и Dock
# Указатели
## unique_ptr:
использовал void ServiceCenter::addItem(std::unique_ptr<InventoryItem> item);
здесь нужен unique_ptr, т.к. item - уникальный по id.
## share_ptr:
использовал std::vector<std::shared_ptr<InventoryItem>> _items;
и std::unordered_map<std::string, std::shared_ptr<ModelSpec>> _model_specs; 
в _items использовал как костыль, чтобы потом получить weak_ptr для focus,
в _model_specs использовал, т.к. может быть несколько item с одинаковой моделью, все они ссылаются на одну ModelSpec. Сам ModelSpec - хранит общую информацию про модель (у меня в коде это просто info="very good" + name, но концептуально можно хранить какую-нибудь важную информацию).
## weak_ptr:
использовал std::weak_ptr<InventoryItem> _focus;
он показывает предмет дня, при этом сам предмет могут удалить окончательно, и focus не должен этому препятсвовать (из за него пришлось сделать _items - shared_ptr)
# Исключения
1) FleetError - общий базис
2) InspectionRejectedError - ошибка техосмотра, бросается если в названии модели есть broken
3) InvalidCommandError - ошибка - "команда некорректна", бросается при написании вводк несуществующей команды
4) InvalidArgumentError - ошибка - "аргументы некорректы", бросается при некорректных аргументах energy < 0, score не в 1..10, и тд
5)  RegistryFullError - ошибка при полном регистре, бросается если привысить Cap
# Шаблон
реализовал шаблон template <typename T, size_t Cap> для class Registry(тут список с небольше чем Cap елементами), а также сделал специализацию для class Registry<std::string, Cap> (тут дополнительная нумерация добавляется в массив)
использую: Registry<std::string, 1000> _registry_items; и Registry<double, 1000> _registry_energy; для записи добавлений/удалений, и вызовов energy соотвественно.
# Креатив
добавил max_energy, count_novice, log, log_energy, RollerSkates - ролики(новый транспорт), RollerSkatesGear - защита для роликов(новый предмет)
# ИИ
не использовал