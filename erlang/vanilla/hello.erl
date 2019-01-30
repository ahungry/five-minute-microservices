-module(hello).
-export([start/1]).

start(StringPort) ->
  io:format("Begin"),
  {Port, _Rest} = string:to_integer(StringPort),
  spawn(fun () -> {ok, Sock} = gen_tcp:listen(Port, [{active, false}]),
                  loop(Sock) end).

loop(Sock) ->
  {ok, Conn} = gen_tcp:accept(Sock),
  Handler = spawn(fun () -> handle(Conn) end),
  gen_tcp:controlling_process(Conn, Handler),
  loop(Sock).

handle(Conn) ->
  gen_tcp:send(Conn, response("\"0.0.1\"")),
  % If content-length is not sent, recv failure and tools will break.
  % Unless you ues shutdown over close.
  gen_tcp:close(Conn).
  %gen_tcp:shutdown(Conn, read_write).

response(Str) ->
  B = iolist_to_binary(Str),
  iolist_to_binary(
    io_lib:fwrite(
             "HTTP/1.0 200 OK\nContent-Type: text/html\nContent-Length: ~p\n\n~s",
             [size(B), B])).
             %"HTTP/1.0 200 OK\nContent-Type: text/html\n\n~s",
             %[B])).
