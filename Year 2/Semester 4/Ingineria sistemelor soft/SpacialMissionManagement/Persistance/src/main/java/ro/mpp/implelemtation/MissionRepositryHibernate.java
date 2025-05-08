package ro.mpp.implelemtation;

import org.hibernate.Session;
import ro.mpp.Mission;
import ro.mpp.MissionRepository;
import ro.mpp.User;
import ro.mpp.util.HibernateUtil;

import java.util.List;
import java.util.Optional;

public class MissionRepositryHibernate implements MissionRepository {
    @Override
    public Optional<Mission> findById(Integer id) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            return Optional.ofNullable(session.get(Mission.class, id));
        }
    }

    @Override
    public List<Mission> findAll() {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            return session.createQuery("from Mission", Mission.class).list();
        }
    }

    @Override
    public Mission save(Mission entity) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.persist(entity);
            session.getTransaction().commit();
            return entity;
        }
    }

    @Override
    public Mission update(Mission entity) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            session.merge(entity);
            session.getTransaction().commit();
            return entity;
        }
    }

    @Override
    public void delete(Integer id) {
        try (Session session = HibernateUtil.getSessionFactory().openSession()) {
            session.beginTransaction();
            Mission mission = session.get(Mission.class, id);
            if (mission != null) {
                session.remove(mission);
            }
            session.getTransaction().commit();
        }
    }

}
