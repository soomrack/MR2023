import asyncio
import websockets

async def send_angle():
    uri = "ws://172.20.10.2:8764"
    async with websockets.connect(uri) as websocket:
        angle = input("Введите значение угла в градусах: ")
        await websocket.send(angle)

asyncio.get_event_loop().run_until_complete(send_angle())
