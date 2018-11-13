using System.Linq;
using System.Web.Http;

namespace WebSiteApp
{
    public class TodoListController : ApiController
    {
        // GET api/<controller>
        public IHttpActionResult Get()
        {
            string[] arrTitle = new string[] { "value1", "value2" };
            return Json(from ii in arrTitle select new { title = ii, isChecked = false });
        }

        // GET api/<controller>/5
        public string Get(int id)
        {
            return "value";
        }

        // POST api/<controller>
        public void Post([FromBody]string value)
        {
        }

        // PUT api/<controller>/5
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE api/<controller>/5
        public void Delete(int id)
        {
        }
    }
}