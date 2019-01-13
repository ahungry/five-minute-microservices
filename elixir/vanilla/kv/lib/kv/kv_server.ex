defmodule KV.Server do
  require Logger

  def accept(port) do
    # The options below mean:
    #
    # 1. `:binary` - receives data as binaries (instead of lists)
    # 2. `packet: :line` - receives data line by line
    # 3. `active: false` - blocks on `:gen_tcp.recv/2` until data is available
    # 4. `reuseaddr: true` - allows us to reuse the address if the listener crashes
    #
    {:ok, socket} =
      :gen_tcp.listen(port, [:binary, packet: :line, active: false, reuseaddr: true])
    Logger.info("Accepting connections on port #{port}")
    loop_acceptor(socket)
  end

  defp loop_acceptor(socket) do
    {:ok, client} = :gen_tcp.accept(socket)
    {:ok, pid} = Task.Supervisor.start_child(KV.Server.TaskSupervisor, fn -> serve(client) end)
    #:ok = :gen_tcp.controlling_process(client, pid)
    x = :gen_tcp.controlling_process(client, pid)
    #serve(client)
    loop_acceptor(socket)
  end

  def get_version(_x) do
    """
    HTTP/1.1 200 OK
    Content-Type: text/html
    Connection: close

    "0.0.1"
    """
  end

  defp serve(socket) do
    # Echo Server
    # socket
    # |> read_line()
    # |> write_line(socket)
    socket
    |> get_version()
    |> write_line(socket)

    close_sock(socket)
    #serve(socket)
  end

  defp read_line(socket) do
    {:ok, data} = :gen_tcp.recv(socket, 0)
    data
  end

  defp write_line(line, socket) do
    :gen_tcp.send(socket, line)
  end

  defp close_sock(socket) do
    # TODO: Fix to use this so we quit erroring out
    :gen_tcp.shutdown(socket, :read_write)
    #:gen_tcp.close(socket)
  end
end
