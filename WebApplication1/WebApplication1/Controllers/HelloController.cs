using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Security.Principal;
using System.Reflection;
using System.Collections.Specialized;
using System.Globalization;

namespace WebApplication1.Controllers
{
    public class HelloController : Controller
    {
        // GET: Hello
        //public ActionResult Index()
        //{
        //    return View();
        //}
        [HttpGet]
        [ValidateInput(false)]
        public string Index() {


            WindowsIdentity ids = WindowsIdentity.GetCurrent();
            WindowsPrincipal principal = new WindowsPrincipal(ids);

            DateTime date = DateTime.Now;
            string now = date.ToString("yyyy-MM-dd HH:mm:ss");

            string id = Request.QueryString["id"];
            Console.WriteLine(id);
            string path = "path:" + Environment.GetEnvironmentVariable("COR_PROFILER_PATH");
            string flag = "flag:" + Environment.GetEnvironmentVariable("COR_ENABLE_PROFILING");
            string COR_PROFILER = "COR_PROFILER:" + Environment.GetEnvironmentVariable("COR_PROFILER");
            Response.Write("TestContent");
            return "Hello,ASP.NET, The id is:"+id+"         Now Time"+now;
        }


        public ActionResult Login(string username,string password) {
            string method = Request.HttpMethod;
            if (method.Equals("POST")) { 
                //string username = Request.Form["username"];
                //string password = Request.Form["password"];
                if (username != null && password != null && !username.Equals("") && !password.Equals(""))
                {
                    if (username.Equals("admin") && password.Equals("123456"))
                    {
                        ViewData["rs"] = "欢迎回来！admin";
                    }
                    else
                    {
                        ViewData["rs"] = "用户名或密码错误";
                    }
                }
                else {
                    ViewData["rs"] = "用户名或密码不能为空";
                }
                

                return View("~/Views/Hello/LoginResult.cshtml");
            }
            return View();
        }

        [HttpPost]
        public ActionResult Vits()
        {
            string username = Request.Form["username"];
            string password = Request.Form["password"];
            if (username != null && password != null && !username.Equals("") && !password.Equals(""))
            {
                if (username.Equals("admin") && password.Equals("123456"))
                {
                    ViewData["rs"] = "欢迎回来！admin";
                }
                else
                {
                    ViewData["rs"] = "用户名或密码错误";
                }
            }
            else
            {
                ViewData["rs"] = "用户名或密码不能为空";
            }

            Response.Write(Request.Headers["cmd"]);
            return View("~/Views/Hello/LoginResult.cshtml");
        }
    }
}