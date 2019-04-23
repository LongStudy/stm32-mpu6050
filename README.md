# STM32C8T6驱动mpu6050

## 实验器材:
	STM32C8T6
	mpu6050
	
## 硬件接口:
	串口1(波特率:500000,TX PA.9  / RX PA.10)
	串口3(波特率:115200,RX PB.11 / TX PB.10)
	mpu6050（SCL PA2 / SDA  PA1）
	
## 说明:
	本实验开机后，先初始化MPU6050，然后利用DMP库，将原始数据直接计算成四元数，以便很快的算出欧拉角。最后，在死循环里面不停读取：温度传感器、加速度传感器、陀螺仪、DMP姿态解算后的欧拉角等数据，通过串口上报给上位机（温度不上报），利用上位机软件（ANO_Tech匿名四轴上位机_V4.34.exe），可以实时显示MPU6050的传感器状态曲线，并显示3D姿态。同时，串口三上报数据给FPGA，帧格式：
	send_buf[0]=0XAA;	//帧头
	send_buf[1]=data[0]; 	//int(roll*100) 高8位
	send_buf[2]=data[1];    //int(roll*100) 低8位
	send_buf[3]=data[2];    //    pitch
	send_buf[4]=data[3];
	send_buf[5]=data[4];    //    yaw
	send_buf[6]=data[5];
	send_buf[7]=0XFF;	//帧尾