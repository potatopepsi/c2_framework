from Crypto.Cipher import AES
import hashlib
import sys
import binascii




def encrypt(plaintext,key):
  encobj = AES.new(key, AES.MODE_GCM)
  ciphertext,authTag=encobj.encrypt_and_digest(plaintext)
  return(ciphertext,authTag,encobj.nonce)

def decrypt(ciphertext,key):
  (ciphertext,  authTag, nonce) = ciphertext
  encobj = AES.new(key,  AES.MODE_GCM, nonce)
  return(encobj.decrypt_and_verify(ciphertext, authTag))

