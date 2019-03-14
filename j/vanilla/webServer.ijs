NB. Run with: ~/jbld/j64/bin/jconsole ~/src/j-scripts/webServer.ijs

coinsert'jsocket' [ require 'socket'             NB.  Sockets library

NB. Globals
LF=10}a. NB. Line feed
port=: 12321

NB. Set up a listener
sock=: > 0 { sdcheck sdsocket AF_INET, SOCK_STREAM, 0
sdbind sock; AF_INET; ''; port
sdlisten sock, 5

smoutput 'Listening on port: '; port

NB. DO block basically
monad define ''
  while. 1 = 1 do.
    NB. w=. > 1 } sdselect '' NB. Returns result;read;write;error
    w=. > 1 } sdselect sock;sock;sock;0 NB. Returns result;read;write;error

    if. #w do.
      sa=. > 1 } ; sdaccept w

      ('HTTP/1.1 200 OK',LF) sdsend sa, 0
      ('Content-Type: application/json',LF) sdsend sa, 0
      ('Content-Length: 7',LF) sdsend sa, 0
      ('Connection: close',LF,LF) sdsend sa, 0
      '"0.0.1"' sdsend sa, 0
      sdclose sa

      NB. This is blocking, aka non-concurrent.  We need some way to thread
      NB. the inbound request if we wanted to allow more than one client to
      NB. connect a time, otherwise one person connects and that's it, they block all others.
      NB. while. #input do. NB. Need to detect when client disconnects
        NB. input sdsend sa, 0
        NB. 'ierr input'=. sdrecv sa, 1024, 0 NB. Destructuring box assignment
	NB. smoutput 'Ierr: '
	NB. smoutput ierr
	NB. smoutput 'input: '
	NB. smoutput input
        NB. input=. > 1 } sdrecv sa, 1024, 0
        NB. sdclose sa NB. Byebye
        NB. smoutput 'I am in the loop still...'
      NB. end.
    end.
  end.
  i.0 0
)

exit 0
