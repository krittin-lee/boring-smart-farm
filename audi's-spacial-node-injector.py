# Audi's Super Dooper Cool Node Injector For Debugging and to Ease Up Your Life (A.S.D.C.N.I.F.D.E.U.Y.L)


import urllib.request
import time
#import tkinter

ip = '127.0.0.1'

def plant():
    pl_light = float(input('Plant light level = '))
    pl_humd = float(input('Plant humidity (%) = '))
    pl_temp = float(input('Plant temperature (ºc)= '))
    pl_pH = float(input('Plant soil pH (0-12)= '))
    urllib.request.urlopen('http://%s:1880/datain_plant?pl_light=%s&pl_humid=%s&pl_temp=%s&pl_pH=%s' % (ip, pl_light, pl_humd, pl_temp, pl_pH))
    print('\nInjected\npl_light = %s\npl_humid = %s\npl_temp = %s\npl_pH = %s \nat %s successfully\n\n' % (pl_light, pl_humd, pl_temp, pl_pH, ip))
    
def animal():
    an_temp = float(input('Animal temperature (ºc)= '))
    an_light = float(input('Animal light level = '))
    urllib.request.urlopen('http://%s:1880/datain_animal?an_light=%s&an_temp=%s' % (ip, an_temp, an_light))
    print('\nInjected\nan_light=%s\nan_temp=%s \nat %s successfully\n\n' % (an_light, an_temp, ip))

def fish():
    fi_kun = float(input('Water opcaity = '))
    urllib.request.urlopen('http://%s:1880/datain_fish?fi_kun=%s' % (ip, fi_kun))
    print('\nInject\nfi_kun = %s \nat %s successfully\n\n' % (fi_kun, ip))

def home():
    home_light = float(input('Home light level = '))
    urllib.request.urlopen('http://%s:1880/datain_home?home_light=%s' % (ip, home_light))
    print('\nInject\nhome_light = %s \nat %s successfully\n\n' % (home_light, ip))

def emergency():
    em = str(input('Emergecny text (Use _ as spacebar or program die) = '))
    urllib.request.urlopen('http://%s:1880/emergency_in?em=%s&s=Node_Farm_Injector' % (ip, em))
    print('\nInject\nem = %s \nat %s successfully\n\n' % (em, ip))
    
def everythings():
    plant()
    #animal()
    fish()
    home()
    emergency()
    
def home_sent():
    urllib.request.urlopen('http://%s:1880/datain_home?home_light=%d' % x)

while(True):
    err = 0
    
    print('- - - - - Atificial Node Farm Injector (1.3) - - - - -\n')
    print("To inject at IP : %s" % ip)
    print('\n|Which sector do you want to input?|')
    print('--DEPARTMENTS--\n• plant\n• animal [Broken for some reason DO NOT USE]\n• fish\n• home\n• emergency\n• all\n\n--PREFERENCES--\n• config_ip\n• exit\n')
    choice = input('Choose => ')

    if choice == 'plant' or choice == 'pl':
        plant()
        
    elif choice == 'animal' or choice == 'an':
        #animal()
        print('It is broken, I told you แล้วน้า')
        print('Try : \nhttp://127.0.0.1:1880//datain_animal?an_light=11&an_temp=22\n')
        print('•')
        time.sleep(0.33)
        print('•')
        time.sleep(0.33)
        print('•')
        time.sleep(0.33)
        print('•\n\n\n')
        
    elif choice == 'fish' or choice == 'fi':
        fish()
        
    elif choice == 'home' or choice == 'ho':
        home()
        
    elif choice == 'all' or choice == 'All':
        everythings()

    elif choice == 'emergency' or choice == 'em':
        emergency()
                       
    elif choice == 'config_ip' or choice == 'config' or choice == 'ip':
        ip = input('New IP desitcation (Might be 192.168.43.141) = ')
        err = 1
    elif choice == 'end' or choice == 'exit':
        break
    else :
        print('You should try again!\n\n\n')
        err = 1

print("\nProgram ended")
