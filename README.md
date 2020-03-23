# WIFI_car

## NodeMCU A

- 操控端 
- Client端
> 接收`PS2`搖桿資料並以逗號分隔打包送至Server端

## NodeMCU B

- 動作端 
- Server端
- SoftwareSerial
> 接收Client端資料並以UART方式將資料直接傳至`Arduino`

## Arduino

- 動作端 
- SoftwareSerial
> 以UART方式接收`NodeMCU B`資料並以逗號分割資料後轉換回`PS2`搖桿各變量

