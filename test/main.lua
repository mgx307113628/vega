local skynet = require "skynet"
require "skynet.manager"

skynet.register_protocol {
	name = "text",
	id = skynet.PTYPE_TEXT,
	pack = function(...) return ... end,
	-- unpack = skynet.tostring,
}

skynet.start(function()
	skynet.error("Server start MGX")
	skynet.fork(function ()
		local count = 0
		local mgx_addr
		while true do
			count = count + 1
			skynet.error("log test: hello skynet " .. count)
			if count == 1 then
				mgx_addr = skynet.launch("mgx")
				skynet.error("CREAT SERVICE: mgx " .. mgx_addr)
			elseif count >= 2 then
				skynet.send(mgx_addr, "text", "ABC_667_" .. count)
			end
			skynet.sleep(500)
		end
	end)
end)
