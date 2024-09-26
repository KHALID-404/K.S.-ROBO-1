import requests,json
city=str(input("Enter Your City Name : "))
x = requests.get(f"https://api.openweathermap.org/data/2.5/weather?q={city}&appid=2664959b966d4fd9c6f0ba6fc9f66979").json()
weather = x["main"]
print(f"\033[1;92mWeather Info & Rain Possibility Of {city}\033[1;90m")
print("\033[1;93mDeveloper : \033[1;94mKHALID-404\033[1;90m")
print("\033[1;95mCurrent Temperature : ",weather["temp"])
print("Current Pressure : ",weather["pressure"])
print("Current Humidity :",weather["humidity"])
print("Cloud : ", (int(x["clouds"]["all"])-30),"%")
try :
    print("\033[1;91mRain Possibility : ",x["rain"]["1h"],"%")
except:
    print("Rain Data Is Not Available")
